//
//  NPresidentDetailController.h
//  Nav
//
//  Created by 佳 刘 on 12-9-26.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
@class President;

#define kNumberOfEditableRows 4
#define kNameRowIndex 0
#define kFromYearRowIndex 1
#define kToYearRowIndex 2
#define kPartyRowIndex 3

#define kLabelTag 4096

@interface NPresidentDetailController : UITableViewController <UITextFieldDelegate> {
    President *president;
    NSArray *fieldLabels;
    NSMutableDictionary *tempValues;
    UITextField *textFieldBeingEdited;
}

@property (nonatomic,retain) President *president;
@property (nonatomic,retain) NSArray *fieldLabels;
@property (nonatomic,retain) NSMutableDictionary *tempValues;
@property (nonatomic,retain) UITextField *textFieldBeingEdited;

-(IBAction)cancel:(id)sender;
-(IBAction)save:(id)sender;
-(IBAction)textFieldDone:(id)sender;

@end
