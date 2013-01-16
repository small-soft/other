//
//  AMCompanyCreditViewController.m
//  AlibabaMobile
//
//  Created by  on 12-2-6.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMCompanyCreditViewController.h"
#import "AMCompanyDetail.h"
#import "AMCompanyDetail.h"
#import "AMCreditResult.h"
#import "AMDataDictConstants.h"
#import "AMCreditSummary.h"
#import "AMCreditRealAuth.h"
#import "AMCreditGuarantee.h"
#import "AMImage.h"

#import "HJManagedImageV.h"
#import "HJObjManager.h"
#import "KeyValueObject.h"
#import "AliCreditFileTitleView.h"
#import "KeyValueObject.h"
#import "AliKeyValueMapView.h"

#import "UIHelp.h"
#import "AliToastView.h"
#import "StringUtils.h"
#import "AMLogUtils.h"
#import "AMLogTypeCode.h"
#import "AliImageButton.h"
#import "AliImageControlFactory.h"


#define RGB(r, g, b) [UIColor colorWithRed:r/255.0 green:g/255.0 blue:b/255.0 alpha:1.0]

@implementation AMCompanyCreditViewController

@synthesize mCreditResult, mCompanyDetail, mMainScrollView;
@synthesize mLoadingView = _mLoadingView;

- (void) viewWillAppear:(BOOL)animated
{
    [AMLogUtils appendLog:APP_COM_DETAL_FIVE];
}

-(void) dealloc
{
    [self.mCompanyDetail release];
    [self.mCreditResult release];
    [self.mMainScrollView release];
//    [self.mLoadingView release];
    self.mLoadingView = nil;
    [super dealloc];
}

-(UIView*)mLoadingView
{
    if (!_mLoadingView) {
        
        NSArray *nib = [[NSBundle mainBundle] loadNibNamed:@"AliLoadingDataView" owner:self options:nil];
        for (id oneObject in nib){
            if ([oneObject isKindOfClass:[AliLoadingDataView class]]){
                _mLoadingView = [(AliLoadingDataView *)oneObject retain];
            }

        }
        _mLoadingView.frame= CGRectMake(0,40,_mLoadingView.frame.size.width,_mLoadingView.frame.size.height);
        _mLoadingView.noDataView.backgroundColor =RGB(0xf0,0xf0,0xf0);
        _mLoadingView.noDataView.frame = CGRectMake(0,0,_mLoadingView.frame.size.width,_mLoadingView.frame.size.height);
        [self.view addSubview:_mLoadingView];
        [_mLoadingView setHidden:NO];
    }
    
    return _mLoadingView;
}

- (void) showNodataMessage
{
    
    [self.mLoadingView setHidden:NO];
    [self.mLoadingView.loadingView setHidden:YES];
    [self.mLoadingView.noDataView setHidden:NO];
}



#pragma mark - View lifecycle

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    mCompanyDetail = [self.dataDict objectForKey:TAB_VIEW_COMPANY_DETAIL];
    mCreditResult = [self.dataDict objectForKey:TAB_VIEW_COMPANY_CREDIT];
    if (mCreditResult && mCompanyDetail) {
        [self initContentData];
    }
    else {
        NSString * errorMsg = NSLocalizedString(@"NO_CREDIT_DATA", nil);
        [[AliToastView MakeToastWithType:TOAST_STYLE_COMMON info:errorMsg] show];
        [self showNodataMessage];
    }
    
    
}
-(void) viewDidUnload
{
//    _mLoadingView = nil;
    self.mLoadingView = nil;
    [super viewDidUnload];
}

- (void) initContentData
{
    //init scrollView
    self.mMainScrollView = [[UIScrollView alloc] initWithFrame:CGRectMake(0, 40, 320, 377)];
    [self.view addSubview:self.mMainScrollView];

    
    int tempX = 0;
    int tempY = 0;
    
    AliCreditFileTitleView * titleView = [[AliCreditFileTitleView alloc] initWithFrame:CGRectMake(tempX, tempY, 320, 100)];
    [titleView setContentDateEx:self.mCreditResult compnayDetail:self.mCompanyDetail];
    titleView.frame = CGRectMake(tempX, tempY, titleView.frame.size.width, titleView.frame.size.height);
    [self.mMainScrollView addSubview:titleView];
    tempY += titleView.frame.size.height ;
    [titleView release];
    
    NSMutableArray * keyValueArray;
    NSString *memberType = mCompanyDetail.memberType;
    if([memberType isEqualToString:MEMBER_TYPE_PERSON]){
        keyValueArray = [[self initPersonalInfo] retain];
    }else if([memberType isEqualToString:MEMBER_TYPE_FREE]){
        //do nothing
        [self showNodataMessage];
        return;
    }else{
        keyValueArray = [[self initEnterpriseInfo] retain];
    }

    AliKeyValueMapView * mappingView = [[AliKeyValueMapView alloc] init];
    mappingView.paddingTop = 0;
    [mappingView setContentArray:keyValueArray maxKeyLabelString:@"四汉字宽"];
    mappingView.frame = CGRectMake(tempX, tempY, mappingView.frame.size.width, mappingView.frame.size.height);
    tempY += mappingView.frame.size.height;
    [self.mMainScrollView addSubview:mappingView];
    [keyValueArray release];
    [mappingView release];
    
    keyValueArray = [[self initCreditInfo] retain];
    mappingView = [[AliKeyValueMapView alloc] init];
    mappingView.alignCenter = NO;
    mappingView.paddingTop = 0;
    [mappingView setContentArray:keyValueArray maxKeyLabelString:@"七个汉字的宽度"];
    mappingView.frame = CGRectMake(tempX, tempY, mappingView.frame.size.width, mappingView.frame.size.height);
    tempY += mappingView.frame.size.height;
    [self.mMainScrollView addSubview:mappingView];
    [mappingView release];
    [keyValueArray release];
    
    self.mMainScrollView.contentSize = CGSizeMake(self.mMainScrollView.frame.size.width, tempY);
}


- (NSMutableArray *) initPersonalInfo
{
    
    NSMutableArray * keyValueArray =[[[NSMutableArray alloc] init] autorelease];
    
    if(mCreditResult.realAuth != nil){

        KeyValueObject *  lineDividedObj = [[KeyValueObject alloc] init];
        lineDividedObj.type = ITEM_STYLE_LINE_DIVIDED;
        [keyValueArray addObject:lineDividedObj];
        [lineDividedObj release];
        
        UIView * renzhengView = [[UIView alloc] init ];
        renzhengView.backgroundColor = [UIColor clearColor];
        renzhengView.frame = CGRectMake(0, 0, 320, 14);
        NSString * memberType = mCompanyDetail.memberType;
        if(memberType != nil){
            int tempX = 10;
            int tempY = 0;
            if([memberType isEqualToString:MEMBER_TYPE_PERSON]){
                
                
                AliImageButton * img = [[AliImageControlFactory sharedInstance] getImageButtonWithType:REAL_AUTH_PERSON_ICON];
                img.frame = CGRectMake(tempX, tempY, img.frame.size.width, img.frame.size.height);
                [renzhengView addSubview:img];
                tempX +=(img.frame.size.width + 10);
                
                UILabel *  desLabel = [[UILabel alloc] init];
                desLabel.text = @"通过个人实名认证";
                desLabel.backgroundColor = [UIColor clearColor];
                desLabel.textColor= [UIHelp colorWithHexString:@"0x2B4D86"];
                desLabel.font = [UIFont systemFontOfSize:14.0f];
                [desLabel sizeToFit];
                desLabel.frame = CGRectMake(tempX, tempY, desLabel.frame.size.width, desLabel.frame.size.height);
                tempY += (desLabel.frame.size.height+10);
                [renzhengView addSubview:desLabel];
                [desLabel release];
            }else if([memberType isEqualToString:MEMBER_TYPE_FREE]){
                //do nothings
            }else{
                AliImageButton * img = [[AliImageControlFactory sharedInstance] getImageButtonWithType:REAL_AUTH_COMPANY_ICON];
                img.frame = CGRectMake(tempX, tempY, img.frame.size.width, img.frame.size.height);
                [renzhengView addSubview:img];
                tempX +=(img.frame.size.width + 10);
                
                UILabel *  desLabel = [[UILabel alloc] init];
                desLabel.text =  [NSString stringWithFormat:@"通过 %@ 认证", mCreditResult.realAuth.avProvider];
                desLabel.backgroundColor = [UIColor clearColor];
                desLabel.textColor= [UIHelp colorWithHexString:@"0x2B4D86"];
                desLabel.font = [UIFont systemFontOfSize:14.0f];
                [desLabel sizeToFit];
                desLabel.frame = CGRectMake(tempX, tempY, desLabel.frame.size.width, desLabel.frame.size.height);
                tempY += (desLabel.frame.size.height+10);
                [renzhengView addSubview:desLabel];
                [desLabel release];
                
            }
           
        }
        
        KeyValueObject * obj = [[KeyValueObject alloc] init];
        obj.type = ITEM_STYLE_CUSTOME;
        obj.value = renzhengView;
        [keyValueArray addObject:obj];
        [obj release];
        [renzhengView release];
        
        obj = [[KeyValueObject alloc] init];
        obj.type = ITEM_STYLE_CUSTOME;
        UIView * titleView = [[UIView alloc] init ];
        titleView.backgroundColor = [UIColor clearColor];
        UILabel * titleLabel = [[UILabel alloc] init];
        titleLabel.backgroundColor = [UIColor clearColor];
        titleLabel.font = [UIFont systemFontOfSize:14.0f];
        titleLabel.textColor = [UIColor blackColor];
        titleLabel.text = @"工商注册信息";
        [titleLabel sizeToFit];
        titleLabel.frame = CGRectMake(10, 0, titleLabel.frame.size.width, titleLabel.frame.size.height);
        [titleView addSubview:titleLabel];
        [titleLabel release];
        titleView.frame = CGRectMake(0, 0, 320, titleLabel.frame.size.height);
        obj.value = titleView;
        [keyValueArray addObject:obj];
        [obj release];
        [titleView release];

        
        //姓名
        if(mCreditResult.realAuth.memberName != nil){
            obj = [[KeyValueObject alloc] init ];
                        
            obj.key = @"姓       名";
            obj.value = mCreditResult.realAuth.memberName;
            [keyValueArray addObject:obj];
            
            [obj release];
        }
        
        //性别
        if(mCreditResult.realAuth.memberSex != nil){
            obj = [[KeyValueObject alloc] init ];
                        
            obj.key = @"性       别";
            obj.value = [mCreditResult.realAuth.memberSex isEqualToString:@"MALE"]?@"男":@"女";
            [keyValueArray addObject:obj];
            
            [obj release];
            
        }
        
        //身份证号
        if(mCreditResult.realAuth.hideIdCardNumber != nil){
            KeyValueObject * obj = [[KeyValueObject alloc] init ];
            
            obj.key = @"身份证号";
            obj.value = mCreditResult.realAuth.hideIdCardNumber;
            [keyValueArray addObject:obj];
            
            [obj release];
            
        }   
    } 
    
    return keyValueArray;
}


- (NSMutableArray *) initEnterpriseInfo
{
    NSMutableArray * keyValueArray =[[[NSMutableArray alloc] init] autorelease];
      
    if(mCreditResult.realAuth != nil){
        KeyValueObject *  lineDividedObj = [[KeyValueObject alloc] init];
        lineDividedObj.type = ITEM_STYLE_LINE_DIVIDED;
        [keyValueArray addObject:lineDividedObj];
        [lineDividedObj release];
        
        UIView * renzhengView = [[UIView alloc] init ];
        renzhengView.backgroundColor = [UIColor clearColor];
        renzhengView.frame = CGRectMake(0, 0, 320, 14);
        NSString * memberType = mCompanyDetail.memberType;
        if(memberType != nil){
            int tempX = 10;
            int tempY = 0;
            if([memberType isEqualToString:MEMBER_TYPE_PERSON]){
                
                
                AliImageButton * img = [[AliImageControlFactory sharedInstance] getImageButtonWithType:REAL_AUTH_PERSON_ICON];
                img.frame = CGRectMake(tempX, tempY, img.frame.size.width, img.frame.size.height);
                [renzhengView addSubview:img];
                tempX +=(img.frame.size.width + 10);
                
                UILabel *  desLabel = [[UILabel alloc] init];
                desLabel.text = @"通过个人实名认证";
                desLabel.backgroundColor = [UIColor clearColor];
                desLabel.textColor= [UIHelp colorWithHexString:@"0x2B4D86"];
                desLabel.font = [UIFont systemFontOfSize:14.0f];
                [desLabel sizeToFit];
                desLabel.frame = CGRectMake(tempX, tempY, desLabel.frame.size.width, desLabel.frame.size.height);
                tempY += (desLabel.frame.size.height+10);
                [renzhengView addSubview:desLabel];
                [desLabel release];
            }else if([memberType isEqualToString:MEMBER_TYPE_FREE]){
                //do nothings
            }else{
                AliImageButton * img = [[AliImageControlFactory sharedInstance] getImageButtonWithType:REAL_AUTH_COMPANY_ICON];
                img.frame = CGRectMake(tempX, tempY, img.frame.size.width, img.frame.size.height);
                [renzhengView addSubview:img];
                tempX +=(img.frame.size.width + 10);
                
                UILabel *  desLabel = [[UILabel alloc] init];
                desLabel.text =  [NSString stringWithFormat:@"通过 %@ 认证", mCreditResult.realAuth.avProvider];
                desLabel.backgroundColor = [UIColor clearColor];
                desLabel.textColor= [UIHelp colorWithHexString:@"0x2B4D86"];
                desLabel.font = [UIFont systemFontOfSize:14.0f];
                [desLabel sizeToFit];
                desLabel.frame = CGRectMake(tempX, tempY, desLabel.frame.size.width, desLabel.frame.size.height);
                tempY += (desLabel.frame.size.height+10);
                [renzhengView addSubview:desLabel];
                [desLabel release];
                
            }
            
        }
        
        KeyValueObject * obj = [[KeyValueObject alloc] init];
        obj.type = ITEM_STYLE_CUSTOME;
        obj.value = renzhengView;
        [keyValueArray addObject:obj];
        [obj release];
        [renzhengView release];
        
        
        obj = [[KeyValueObject alloc] init];
        obj.type = ITEM_STYLE_CUSTOME;
        UIView * titleView = [[UIView alloc] init ];
        titleView.backgroundColor = [UIColor clearColor];
        UILabel * titleLabel = [[UILabel alloc] init];
        titleLabel.backgroundColor = [UIColor clearColor];
        titleLabel.font = [UIFont systemFontOfSize:14.0f];
        titleLabel.textColor = [UIColor blackColor];
        titleLabel.text = @"工商注册信息";
        [titleLabel sizeToFit];
        titleLabel.frame = CGRectMake(10, 0, titleLabel.frame.size.width, titleLabel.frame.size.height);
        [titleView addSubview:titleLabel];
        [titleLabel release];
        titleView.frame = CGRectMake(0, 0, 320, titleLabel.frame.size.height);
        obj.value = titleView;
        [keyValueArray addObject:obj];
        [obj release];
        [titleView release];

        //公司名称
        if(mCreditResult.realAuth.companyName != nil){
            obj = [[KeyValueObject alloc] init ];
            
            obj.key = @"公司名称";
            obj.value = mCreditResult.realAuth.companyName;
            [keyValueArray addObject:obj];
            
            [obj release];
        }
        
        //地址
        if(mCreditResult.realAuth.companyAddress != nil){
            obj = [[KeyValueObject alloc] init ];
                        
            obj.key = @"地       址";
            obj.value = mCreditResult.realAuth.companyAddress;
            [keyValueArray addObject:obj];
            
            [obj release];

        }
           
        //注册资本
        if(mCreditResult.realAuth.regCapital != nil
           && mCreditResult.realAuth.currencyType != nil
           && mCreditResult.realAuth.currencyUnit != nil
           && mCreditResult.realAuth.regCapital.doubleValue > 0){
            obj = [[KeyValueObject alloc] init ];
            
            obj.key = @"注册资金";
            obj.value = [NSString stringWithFormat:@"%@%@%@", mCreditResult.realAuth.regCapital, mCreditResult.realAuth.currencyUnit, mCreditResult.realAuth.currencyType];
            [keyValueArray addObject:obj];
            
            [obj release];
            
        }
           
        //成立日期
        if(mCreditResult.realAuth.establishedYear != nil
           && mCreditResult.realAuth.establishedYear.longValue > 0){
            obj = [[KeyValueObject alloc] init ];
//            
//            NSDateFormatter *formatter = [[NSDateFormatter alloc] init];
//            [formatter setDateFormat:@"yyyy年mm月dd日"];
//            NSString * dateStr = [formatter stringFromDate: [NSDate dateWithTimeIntervalSince1970:mCreditResult.realAuth.establishedYear.doubleValue]];
//            [formatter release];
            
            NSString * dateStr = [StringUtils getDateStrShort: mCreditResult.realAuth.establishedYear.doubleValue /1000];
                        
            obj.key = @"成立日期";
            obj.value = dateStr;
            
            [keyValueArray addObject:obj];
            
            [obj release];
            
        }
           
        //经营范围
        if(mCreditResult.realAuth.companyBusinessLine != nil){
            obj = [[KeyValueObject alloc] init ];
            
            obj.key = @"经营范围";
            obj.value = mCreditResult.realAuth.companyBusinessLine;
            [keyValueArray addObject:obj];
            
            [obj release];
            
        }
    }
    return keyValueArray;
}

- (NSMutableArray *) initCreditInfo
{
    NSMutableArray * keyValueArray = [[[NSMutableArray alloc] init] autorelease];
    
    KeyValueObject *  lineDividedObj = [[KeyValueObject alloc] init];
    lineDividedObj.type = ITEM_STYLE_LINE_DIVIDED;
    [keyValueArray addObject:lineDividedObj];
    [lineDividedObj release];
    
    UIView * chengbaoView = [[UIView alloc] init ];
    chengbaoView.backgroundColor = [UIColor clearColor];
    chengbaoView.frame = CGRectMake(0, 0, 320, 14);
    if(mCreditResult.guarantee.totalCreditMoney != nil
       && mCreditResult.guarantee.totalCreditMoney.floatValue > 0){
        int tempX = 15;
        int tempY = 0;

        
        AliImageButton * chengbaoIv = [[AliImageControlFactory sharedInstance] getImageButtonWithType:CHENG_BAO_ICON];
        chengbaoIv.frame = CGRectMake(tempX, tempY, chengbaoIv.frame.size.width, chengbaoIv.frame.size.height);
        [chengbaoView addSubview:chengbaoIv];
        tempX += (chengbaoIv.frame.size.width);
        
        UILabel *  label5 = [[UILabel alloc] init];
        label5.text = [NSString stringWithFormat:@"诚信保障  ¥%@", mCreditResult.guarantee.totalCreditMoney];
        label5.backgroundColor = [UIColor clearColor];
        label5.textColor= [UIHelp colorWithHexString:@"0x2B4D86"];
        label5.font = [UIFont systemFontOfSize:14.0f];
        [label5 sizeToFit];
        label5.frame = CGRectMake(tempX, tempY , label5.frame.size.width, label5.frame.size.height);
        [chengbaoView addSubview:label5];
        tempY +=(label5.frame.size.height);
        [label5 release];
    }
    KeyValueObject * obj = [[KeyValueObject alloc] init];
    obj.type = ITEM_STYLE_CUSTOME;
    obj.value = chengbaoView;
    [keyValueArray addObject:obj];
    [obj release];
    [chengbaoView release];
    
    if(mCreditResult.guarantee != nil){
//        KeyValueObject * obj = [[KeyValueObject alloc] init];
//        obj.type = ITEM_STYLE_TITLE;
//        obj.value =@"诚信保障信息";
//        [keyValueArray addObject:obj];
//        [obj release];
        
        
        //可用保障金
        if(mCreditResult.guarantee.totalBalanceMoney != nil){
            obj = [[KeyValueObject alloc] init];
            
            obj.key = @"可用保障金";
            obj.value = [NSString stringWithFormat:@"%.2f" ,mCreditResult.guarantee.totalBalanceMoney.floatValue];
            [keyValueArray addObject:obj];
            
            [obj release];
        }
        
        //冻结保障金
        if(mCreditResult.guarantee.freezeRecordsNum != nil){
            obj = [[KeyValueObject alloc] init];
            
            obj.key = @"冻结保障金";
            obj.value = [NSString stringWithFormat:@"%.2f" ,mCreditResult.guarantee.freezeRecordsNum.floatValue];
            [keyValueArray addObject:obj];
            
            [obj release];
        }
        
        //已保障的交易数
        if(mCreditResult.guarantee.freezeRecordsNum != nil){
            obj = [[KeyValueObject alloc] init];
            
            obj.key = @"已保障的交易数";
            obj.value = [NSString stringWithFormat:@"%d笔" ,mCreditResult.guarantee.freezeRecordsNum.intValue];
            [keyValueArray addObject:obj];
            
            [obj release];
        }
        
        //保障中的交易数
        if(mCreditResult.guarantee.unFreezeRecordsNum != nil){
            obj = [[KeyValueObject alloc] init];
            
            obj.key = @"保障中的交易数";
            obj.value = [NSString stringWithFormat:@"%d笔", mCreditResult.guarantee.unFreezeRecordsNum.intValue];
            [keyValueArray addObject:obj];
            
            [obj release];
        }
        
    }
    return keyValueArray;
}


@end
