//
//  AMCompanyDetailViewController.m
//  AlibabaMobile
//
//  Created by  on 12-2-6.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMCompanyDetailViewController.h"
#import "AMCompanyDetail.h"
#import "AMCompanyIndustry.h"
#import "UIHelp.h"
#import "AMDataDictConstants.h"
#import "KeyValueObject.h"
#import "AMBusinessRegistration.h"
#import "StringUtils.h"
#import "AliKeyValueMapView.h"
#import "AliMemberContactView.h"
#import "AMLogUtils.h"
#import "AMLogTypeCode.h"
#import "AMIMTalkViewController.h"
#import "LoginToken.h"

@implementation AMCompanyDetailViewController

@synthesize mMainScrollView;

#pragma mark - View lifecycle

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    mCompanyDetail = [self.dataDict objectForKey:TAB_VIEW_COMPANY_DETAIL];
    
    if(mCompanyDetail != nil){
        [self initContentDataEx ];
    }
    
    isTalkAfterWwLogin = NO;
}

- (void) viewWillAppear:(BOOL)animated
{
    [super viewWillDisappear:animated];
    [AMLogUtils appendLog:APP_COM_DETAL_FOUR];
    
    if (isTalkAfterWwLogin) {
        [[NSNotificationCenter defaultCenter] removeObserver:self];
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(onWwLoginSucc) name:NOTIFICATION_WW_LOGIN_SUCC object:nil];
    }
}

- (void)viewWillDisappear:(BOOL)animated {
  	[super viewWillDisappear:animated];
    
    [[NSNotificationCenter defaultCenter] removeObserver:self];
}

-(void) dealloc
{
    [[NSNotificationCenter defaultCenter] removeObserver:self];
    [mCompanyDetail release];
    [mMainScrollView release];
    [super dealloc];
}

- (void) initContentDataEx
{
    int tempX = 0;
    int tempY = 0;

    NSMutableArray * keyValueArray = [[NSMutableArray alloc] init];
    
    //公司名
    if(mCompanyDetail.name != nil){
        KeyValueObject * keyValueObj = [[KeyValueObject alloc] init];

        keyValueObj.key = @"公司名";
        keyValueObj.value = mCompanyDetail.name;
        [keyValueArray addObject:keyValueObj];
        
        [keyValueObj release];
    }
    
    //会员类型
    if(mCompanyDetail.memberType != nil)
    {
        KeyValueObject * keyValueObj = [[KeyValueObject alloc] init];
        keyValueObj.key = @"会员类型";
        keyValueObj.value = [self getMemberType:mCompanyDetail.memberType];
        [keyValueArray addObject:keyValueObj];
        [keyValueObj release];
        
    }
    
    //公司注册地
    if(mCompanyDetail.registration != nil
       && mCompanyDetail.registration.foundedPlace != nil){
        KeyValueObject * keyValueObj = [[KeyValueObject alloc] init];
        keyValueObj.key = @"公司注册地";
        keyValueObj.value = mCompanyDetail.registration.foundedPlace;
        [keyValueArray addObject:keyValueObj];
         [keyValueObj release];
    }
    
    //注册资本
    if(mCompanyDetail.registration != nil
       && mCompanyDetail.registration.regCapital != nil 
       && mCompanyDetail.registration.regCapital.doubleValue > 0
       && mCompanyDetail.registration.currencyType != nil
       && mCompanyDetail.registration.currencyType.name != nil){
        KeyValueObject * keyValueObj = [[KeyValueObject alloc] init];
        keyValueObj.key = @"注册资本";
        keyValueObj.value = [NSString stringWithFormat:@"%@万元%@",mCompanyDetail.registration.regCapital, mCompanyDetail.registration.currencyType.name];
        [keyValueArray addObject:keyValueObj];
        [keyValueObj release];
    }
    
    //公司地点
    if(mCompanyDetail.address != nil && [StringUtils getAddressString:mCompanyDetail.address] != nil ){
        KeyValueObject * keyValueObj = [[KeyValueObject alloc] init];
        keyValueObj.key = @"公司地点";
        keyValueObj.value = [StringUtils getAddressString:mCompanyDetail.address];
        [keyValueArray addObject:keyValueObj];
         [keyValueObj release];
    }
    
    //成立时间
    if(mCompanyDetail.registration.establishedYear){
        KeyValueObject * keyValueObj = [[KeyValueObject alloc] init];
        keyValueObj.key = @"公司成立时间";
        keyValueObj.value = mCompanyDetail.registration.establishedYear;
        [keyValueArray addObject:keyValueObj];
        [keyValueObj release];
    }
    
    //法定代表人
    if(mCompanyDetail.registration != nil 
       && mCompanyDetail.registration.principal != nil){
        KeyValueObject * keyValueObj = [[KeyValueObject alloc] init];
        keyValueObj.key = @"法定代表人";
        keyValueObj.value = mCompanyDetail.registration.principal;
        [keyValueArray addObject:keyValueObj];
        [keyValueObj release];
    }
    
    //主营产品
    if(mCompanyDetail.productionService != nil
       && mCompanyDetail.productionService.count > 0){
        KeyValueObject * keyValueObj = [[KeyValueObject alloc] init];
        keyValueObj.key = @"主营产品";
        keyValueObj.value = [StringUtils getStringArrayString:mCompanyDetail.productionService];
        [keyValueArray addObject:keyValueObj];
         [keyValueObj release];
    }
    
    
    //员工人数
    if(mCompanyDetail.employeesCount != nil)
    {
        KeyValueObject * keyValueObj = [[KeyValueObject alloc] init];
        keyValueObj.key = @"员工人数";
        keyValueObj.value = mCompanyDetail.employeesCount;
        [keyValueArray addObject:keyValueObj];
          [keyValueObj release];
    }
    
    //经营模式
    if(mCompanyDetail.bizType != nil)
    {
        KeyValueObject * keyValueObj = [[KeyValueObject alloc] init];
        keyValueObj.key = @"经营模式";
        keyValueObj.value = [self getBizType:mCompanyDetail.bizType];
        [keyValueArray addObject:keyValueObj];
        [keyValueObj release];
        
    }
    
    if(mCompanyDetail.bizType != nil){
        NSString * typeCode = mCompanyDetail.bizType;
        if([typeCode isEqualToString: BIZ_TYPE_MANUFACTURER]){
            if(mCompanyDetail.manufactureSupplied.boolValue){
                //产房面积
                if(mCompanyDetail.industry != nil
                   && mCompanyDetail.industry.factorySize != nil
                   && ![mCompanyDetail.industry.factorySize isEqualToString:@""])
                {
                    KeyValueObject * keyValueObj = [[KeyValueObject alloc] init];
                    keyValueObj.key = @"产房面积";
                    keyValueObj.value = [NSString stringWithFormat:@"%@平米", mCompanyDetail.industry.factorySize];
                    [keyValueArray addObject:keyValueObj];
                    [keyValueObj release];
                    
                }
                
                //加工方式
                if(mCompanyDetail.industry != nil
                   && mCompanyDetail.industry.manufactureType != nil)
                {
                    KeyValueObject * keyValueObj = [[KeyValueObject alloc] init];
                    keyValueObj.key = @"加工方式";
                    
                    NSMutableString * manuType = [NSMutableString stringWithString: @""];
                    int size = mCompanyDetail.industry.manufactureType.count;
                    for(int i=0; i<size;i++){
                        [manuType appendString:[mCompanyDetail.industry.manufactureType objectAtIndex:i]];
                        if(i <size-1){
                            [manuType appendString:@","];
                        }
                    }
                    keyValueObj.value = manuType;
                    [keyValueArray addObject:keyValueObj];
                    [keyValueObj release];
                    
                }
                
                //工艺
                if(mCompanyDetail.industry != nil
                   && mCompanyDetail.industry.technologyType != nil)
                {
                    KeyValueObject * keyValueObj = [[KeyValueObject alloc] init];
                    keyValueObj.key = @"工艺";
                    
                    NSMutableString * techType = [NSMutableString stringWithString: @""];
                    int size = mCompanyDetail.industry.technologyType.count;
                    for(int i=0; i<size;i++){
                        [techType appendString:[mCompanyDetail.industry.technologyType objectAtIndex:i]];
                        if(i <size-1){
                            [techType appendString:@","];
                        }
                    }
                    keyValueObj.value = techType;
                    [keyValueArray addObject:keyValueObj];
                    [keyValueObj release];
                    
                }
                
                
            }else{
                
                
                //产房面积
                if(mCompanyDetail.industry != nil
                   && mCompanyDetail.industry.factorySize != nil
                   && ![mCompanyDetail.industry.factorySize isEqualToString:@""])
                {
                    KeyValueObject * keyValueObj = [[KeyValueObject alloc] init];
                    keyValueObj.key = @"产房面积";
                    keyValueObj.value = [NSString stringWithFormat:@"%@平米", mCompanyDetail.industry.factorySize];
                    [keyValueArray addObject:keyValueObj];
                    [keyValueObj release];
                    
                }
                
                //月产量
                if(mCompanyDetail.industry != nil
                   && mCompanyDetail.industry.productionCapacity != nil
                   && ![mCompanyDetail.industry.productionCapacity isEqualToString:@""]
                   && mCompanyDetail.industry.productionUnit != nil)
                {
                    KeyValueObject * keyValueObj = [[KeyValueObject alloc] init];
                    keyValueObj.key = @"月产量";
                    keyValueObj.value = [NSString stringWithFormat:@"%@%@", mCompanyDetail.industry.productionCapacity, mCompanyDetail.industry.productionUnit];
                    [keyValueArray addObject:keyValueObj];
                    [keyValueObj release];
                    
                }
                
                //主要市场
                if(mCompanyDetail.industry != nil
                   && mCompanyDetail.industry.warehouseArea != nil
                   && ![mCompanyDetail.industry.warehouseArea isEqualToString:@""])
                {
                    KeyValueObject * keyValueObj = [[KeyValueObject alloc] init];
                    keyValueObj.key = @"主要市场";
                    keyValueObj.value = mCompanyDetail.industry.warehouseArea;
                    [keyValueArray addObject:keyValueObj];
                    [keyValueObj release];
                    
                }
            }
        }else if([typeCode isEqualToString: BIZ_TYPE_WHOLESALE]){
            
            //年营业额
            if(mCompanyDetail.industry != nil
               && mCompanyDetail.industry.annualRevenue != nil
               && ![mCompanyDetail.industry.annualRevenue isEqualToString:@""])
            {
                KeyValueObject * keyValueObj = [[KeyValueObject alloc] init];
                keyValueObj.key = @"年营业额";
                keyValueObj.value = mCompanyDetail.industry.annualRevenue;
                [keyValueArray addObject:keyValueObj];
                [keyValueObj release];
                
            }

            
            //产房面积
            if(mCompanyDetail.industry != nil
               && mCompanyDetail.industry.factorySize != nil
               && ![mCompanyDetail.industry.factorySize isEqualToString:@""])
            {
                KeyValueObject * keyValueObj = [[KeyValueObject alloc] init];
                keyValueObj.key = @"产房面积";
                keyValueObj.value = [NSString stringWithFormat:@"%@平米", mCompanyDetail.industry.factorySize];
                [keyValueArray addObject:keyValueObj];
                [keyValueObj release];
                
            }
        
            //主要市场
            if(mCompanyDetail.industry != nil
               && mCompanyDetail.industry.warehouseArea != nil
               && ![mCompanyDetail.industry.warehouseArea isEqualToString:@""])
            {
                KeyValueObject * keyValueObj = [[KeyValueObject alloc] init];
                keyValueObj.key = @"主要市场";
                keyValueObj.value = mCompanyDetail.industry.warehouseArea;
                [keyValueArray addObject:keyValueObj];
                [keyValueObj release];
                
            }

        }else if([typeCode isEqualToString:BIZ_TYPE_INVESTMENT]){
            
        }else if([typeCode isEqualToString:BIZ_TYPE_TRADE]){
           
        }else{
            
        }
           

    }
    
//    KeyValueObject *lineDividedObj = [[KeyValueObject alloc] init];
//    lineDividedObj.type = ITEM_STYLE_LINE_DIVIDED;
//    [keyValueArray addObject:lineDividedObj];
//    [lineDividedObj release];
    
    AliKeyValueMapView * mappingView = [[AliKeyValueMapView alloc] init];
    [mappingView setContentArray:keyValueArray maxKeyLabelString:@"五个汉子宽"]; 
    mappingView.frame = CGRectMake(tempX, tempY, 320, mappingView.frame.size.height);
    mappingView.paddingBottom = 0;
    [self.mMainScrollView addSubview:mappingView];
    tempY += mappingView.frame.size.height;
    [mappingView release];
    [keyValueArray release];

    //add contact info section
    AliMemberContactView * contactView = [[AliMemberContactView alloc]init];
    contactView.memberContactDelegate = self;
    AMMemberBrief * memberBrief = [[AMMemberBrief alloc] init];
    memberBrief.contact = mCompanyDetail.contact;
    memberBrief.person = mCompanyDetail.person;
    
    [contactView setContactInfo:memberBrief memberId:nil];
    contactView.frame = CGRectMake(tempX, tempY, contactView.frame.size.width, contactView.frame.size.height);
    [self.mMainScrollView addSubview:contactView];
    tempY += contactView.frame.size.height;

    [memberBrief release];
    [contactView release];
    
    //add company describe
    keyValueArray = [[NSMutableArray alloc] init];
    
//    lineDividedObj = [[KeyValueObject alloc] init];
//    lineDividedObj.type = ITEM_STYLE_LINE_DIVIDED;
//    [keyValueArray addObject:lineDividedObj];
//    [lineDividedObj release];
    
    //公司简介
    if(mCompanyDetail.summary != nil){
        
        KeyValueObject * keyValueObj = [[KeyValueObject alloc] init];
        keyValueObj.type = ITEM_STYLE_CUSTOME;

        UILabel * label = [[UILabel alloc] init];
        label.backgroundColor = [UIColor clearColor];
        label.font = [UIFont systemFontOfSize:14.0f];
        label.textAlignment = UITextAlignmentLeft;
        label.numberOfLines = 1;
        label.textColor = [UIHelp colorWithHexString:@"0x666666"];
        label.text = @"公司简介:";
        label.frame = CGRectMake(10, 0, 300, 14);
        keyValueObj.value = label;
        [keyValueArray addObject:keyValueObj];
        [keyValueObj release];
        [label release];
        
        keyValueObj = [[KeyValueObject alloc] init];
        keyValueObj.type = ITEM_STYLE_CUSTOME;
        label = [[UILabel alloc] init];
        label.backgroundColor = [UIColor clearColor];
        label.font = [UIFont systemFontOfSize:14.0f];
        label.lineBreakMode = UILineBreakModeWordWrap;
        label.numberOfLines = 0;
        label.textColor = [UIHelp colorWithHexString:@"0x333333"];
        label.text = mCompanyDetail.summary;
        label.frame = CGRectMake(10, 0, 300, [UIHelp getLabelSizeWithFont:label.font labelString:label.text labelWidth:300].height);
        keyValueObj.value = label;
        [keyValueArray addObject:keyValueObj];
        [keyValueObj release];
        [label release];
       
    }
    mappingView = [[AliKeyValueMapView alloc] init];
    [mappingView setContentArray:keyValueArray maxKeyLabelString:@"六个汉子宽啊"]; 
    mappingView.frame = CGRectMake(tempX, tempY, 320, mappingView.frame.size.height);
    mappingView.paddingBottom = 0;
    [self.mMainScrollView addSubview:mappingView];
    tempY += mappingView.frame.size.height;
    [mappingView release];
    [keyValueArray release];

    
    self.mMainScrollView.contentSize = CGSizeMake(self.mMainScrollView.frame.size.width, tempY);
}

- (NSString *) getMemberType:(NSString *)typeCode
{
    NSString *  const MEMBER_TYPE_ENTERPRICE = @"enterprise";//企业会员
    NSString *  const MEMBER_TYPE_PERSON = @"person";//个人会员
    NSString *  const MEMBER_TYPE_ETC = @"etc";//海外会员
    NSString *  const MEMBER_TYPE_SM = @"sm";//专业市场会员
    NSString *  const MEMBER_TYPE_EM = @"em";//展会会员
    NSString *  const MEMBER_TYPE_VIP = @"vip";//VIP商城会员
    NSString *  const MEMBER_TYPE_FREE = @"free";//免费会员
    
    if([typeCode isEqualToString:MEMBER_TYPE_ENTERPRICE]){
        return @"企业会员";
    }else if([typeCode isEqualToString:MEMBER_TYPE_PERSON]){
        return @"个人会员";
    }else if([typeCode isEqualToString:MEMBER_TYPE_ETC]){
        return @"海外会员";
    }else if([typeCode isEqualToString:MEMBER_TYPE_SM]){
        return @"专业市场会员";
    }else if([typeCode isEqualToString:MEMBER_TYPE_EM]){
        return @"展会会员";
    }else if([typeCode isEqualToString:MEMBER_TYPE_VIP]){
        return @"VIP商城会员";
    }else if([typeCode isEqualToString:MEMBER_TYPE_FREE]){
        return @"免费会员";
    }else{
        return @"其他";
    }
}


- (NSString *) getBizType:(NSString *) typeCode
{
    if([typeCode isEqualToString: BIZ_TYPE_MANUFACTURER])
        return @"生产加工";
    else if([typeCode isEqualToString: BIZ_TYPE_WHOLESALE])
        return @"经销批发";
    else if([typeCode isEqualToString:BIZ_TYPE_INVESTMENT])
        return @"招商代理";
    else if([typeCode isEqualToString:BIZ_TYPE_TRADE])
        return @"商业服务";
    else
        return @"其他";
}

- (void) onWwLoginSucc {
    if (isTalkAfterWwLogin) {
        [self enterTalk];
        isTalkAfterWwLogin = NO;
    }
}

- (void) enterTalk {
    if (mCompanyDetail && mCompanyDetail.person.name) {
        AMIMTalkViewController * talkViewController = [[AMIMTalkViewController alloc] initWithParam:NO:NO:nil:mCompanyDetail.person.wwCode : mCompanyDetail.person.name];
        [talkViewController setHidesBottomBarWhenPushed:YES];
        [self.navigationController pushViewController:talkViewController animated:YES];
        [talkViewController release];
    }
}

-(void)wangWangDidSelected {
    if([LoginToken isWangWangLogined]) {
        [self enterTalk];
    } else {
        isTalkAfterWwLogin = YES;
        [[NSNotificationCenter defaultCenter] postNotificationName:NOTIFICATION_DO_WW_LOGIN object:nil];
        
        [[NSNotificationCenter defaultCenter] removeObserver:self];
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(onWwLoginSucc) name:NOTIFICATION_WW_LOGIN_SUCC object:nil];
    }
}

@end
