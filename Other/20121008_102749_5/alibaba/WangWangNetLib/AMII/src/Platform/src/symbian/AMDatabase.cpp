/*
 * AMDataBase.cpp
 *
 *  Created on: 2010-3-2
 *      Author: qing.chen
 */

#include <e32std.h>
#include <badesca.h>    // CDesCArrayFlat (cannot be forward declarated)
#include <d32dbms.h>    // RDbStoreDatabase
#include <f32file.h>    // RFs
#include <s32file.h>
#include <eikenv.h>
#include <bautils.h>    // file helpers

#include "AMDatabase.h"

#define REINTERPRET( Type, NewValue, OldValue ) Type NewValue = reinterpret_cast<Type>( OldValue )

struct DabaBaseInternal
	{
	RDbStoreDatabase* db;
	CPermanentFileStore* filestore;
	};

AMInt32 AMDbCreate(const AMChar* pDbName)
	{
	REINTERPRET( const unsigned char*, temp, pDbName );
	TPtrC8 ptr( temp );
	TFileName name;
	name.Copy( ptr );
	
	RDbStoreDatabase Db;
	
	CPermanentFileStore* iFileStore = NULL;
	
    TRAPD(error,
    	iFileStore = CPermanentFileStore::ReplaceL(CEikonEnv::Static()->FsSession(), name, 
    		EFileRead|EFileWrite);
    	iFileStore->SetTypeL(iFileStore->Layout());// Set file store type
    	TStreamId id = Db.CreateL(iFileStore);// Create stream object
    	iFileStore->SetRootL(id);// Keep database id as root of store
    	iFileStore->CommitL();// Complete creation by commiting
    	);
    
    Db.Close();
    delete iFileStore;
    
    if(error!=KErrNone)
    {
    	return error;
    }

    return KErrNone;
	}

int AMDbRemoveByName(const char* pDbName)
	{
	REINTERPRET( const unsigned char*, temp, pDbName );
	TPtrC8 ptr( temp );
	TFileName name;
	name.Copy( ptr );
	
    if(!BaflUtils::FileExists(CEikonEnv::Static()->FsSession(), name))
        {
            return KErrNotFound;
        }

    CEikonEnv::Static()->FsSession().Delete(name);
    return KErrNone;
	}

AMInt32 AMDbOpen(AMDatabase* db, const AMChar* pDbName)
	{
	REINTERPRET( const unsigned char*, temp, pDbName );
	TPtrC8 ptr( temp );
	TFileName name;
	name.Copy( ptr );
	
    if(!BaflUtils::FileExists(CEikonEnv::Static()->FsSession(), name))
        {
            return KErrNotFound;
        }
    
    RDbStoreDatabase* Db = new ( ELeave ) RDbStoreDatabase;
    
    CPermanentFileStore* iFileStore = NULL;
    
	TRAPD(error, 
		iFileStore = CPermanentFileStore::OpenL(CEikonEnv::Static()->FsSession(), name, 
			EFileRead|EFileWrite);
		iFileStore->SetTypeL(iFileStore->Layout());/* Set file store type*/
		Db->OpenL(iFileStore,iFileStore->Root())
		);
	
    if(error!=KErrNone)
    {
    	return error;
    }
    
    DabaBaseInternal* ret = new ( ELeave ) DabaBaseInternal;
    ret->db = Db;
    ret->filestore = iFileStore;
    *db = ret;
    
    return KErrNone;
	}

AMInt32 AMDbClose(AMDatabase db)
	{
	REINTERPRET( DabaBaseInternal*, temp, db );
	
    temp->db->Close();
    delete temp->db;
    if(temp->filestore)
        {
        delete temp->filestore;
        temp->filestore = NULL;
        }
    delete temp;
    return KErrNone;
	}

AMInt32 AMDbExecSQL(AMDatabase db, const AMChar* strSQL, AMDatabaseView* pView)
	{
	REINTERPRET( const unsigned char*, t, strSQL );
	TPtrC8 ptr( t );
	TBuf<256> command;
	command.Copy( ptr );
	
	command.TrimLeft();
	command.UpperCase();
	
	TInt index = command.Find( _L("SELECT") );
	
	REINTERPRET( DabaBaseInternal*, temp, db );
	
	if( 0 != index )
		{
		temp->db->Execute( command );
		}
	else
		{
	    RDbView* view = new ( ELeave ) RDbView;
	    User::LeaveIfError(
	        view->Prepare(*temp->db, TDbQuery(command), RDbView::EReadOnly));
	    User::LeaveIfError(view->EvaluateAll());
	    *pView = view;
		}
	}

AMInt32 AMDbViewClose(AMDatabaseView view)
	{
	REINTERPRET( RDbView*, temp, view );
	temp->Close();
	}

AMInt32 AMDbViewFirst(AMDatabaseView view)
	{
	REINTERPRET( RDbView*, temp, view );
	temp->FirstL();
	}

AMInt32 AMDbViewPrevious(AMDatabaseView view)
	{
	REINTERPRET( RDbView*, temp, view );
	temp->PreviousL();
	}

AMInt32 AMDbViewNext(AMDatabaseView view)
	{
	REINTERPRET( RDbView*, temp, view );
	temp->NextL();
	}

AMInt32 AMDbViewLast(AMDatabaseView view)
	{
	REINTERPRET( RDbView*, temp, view );
	temp->LastL();
	}

AMInt32 AMDbViewGetCurrentSize(AMDatabaseView view)
	{
	REINTERPRET( RDbView*, temp, view );
	temp->GetL();
	TInt size = 0;
	for( TInt i = 1; i <= temp->ColCount(); ++i )
		{
		size += temp->ColDes( i ).Length();
		}
	return size;
	}

AMInt32 AMDbViewGetCurrentRecord(AMDatabaseView view, AMInt8* pContent, AMInt32 size)
	{
	REINTERPRET( unsigned char*, t, pContent );
	TPtr8 ptr( t, size );
	REINTERPRET( RDbView*, temp, view );
	temp->GetL();
	for( TInt i = 1; i <= temp->ColCount(); ++i )
		{
		ptr.Append( temp->ColDes( i ) );
		}
	}

AMInt32 AMDbViewGetColumnIndex(AMDatabaseView view, AMChar* columnName)
	{
	REINTERPRET( RDbView*, temp, view );
	CDbColSet* colSet = temp->ColSetL();
	CleanupStack::PushL(colSet);
	REINTERPRET( const unsigned char*, t, columnName );
	TPtrC8 ptr( t );
	TBuf<256> name;
	name.Copy( ptr );
	TInt ret = colSet->ColNo( name );
	CleanupStack::PopAndDestroy(colSet);
	return ret;
	}

AMInt32 AMDbViewGetCurrentData(AMDatabaseView view, AMInt32 nColumnIndex, AMInt8* pContent, AMInt32* size)
	{
	REINTERPRET( unsigned char*, t, pContent );
	TPtr8 ptr( t, *size );
	REINTERPRET( RDbView*, temp, view );
	temp->GetL();
	ptr.Append( temp->ColDes8( nColumnIndex ) );
	}

AMInt32 AMDbViewRows(AMDatabaseView view)
	{
	REINTERPRET( RDbView*, temp, view );
	return temp->CountL();
	}
