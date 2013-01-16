//
//  AMOfferDetailController.m
//  AlibabaMobile
//
//  Created by mardin partytime on 2/2/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "AMOfferDetailViewController.h"
#import <QuartzCore/QuartzCore.h>
#import "AMOfferDetail.h"
#import "StringUtils.h"
#import "AMOfferRate.h"
#import "AMDataDictConstants.h"
#import "AMTradeInfo.h"
#import "OHAttributedLabel.h"
#import "UIHelp.h"
#import "AMOfferGalleryViewController.h"
#import "AliPriceRangeView.h"
#import "KeyValueObject.h"
#import "AliKeyValueMapView.h"
#import "AliImageControlFactory.h"
#import "AliImageButton.h"
#import "AliSatisfyRateView.h"
#import "AliSmallRemoteImageGallery.h"
#import "AMCreditBase.h"
#import "AMLogUtils.h"
#import "AMLogTypeCode.h"
#import "AliMemberContactView.h"
#import "AMIMTalkViewController.h"
#import "LoginToken.h"


@implementation AMOfferDetailViewController

@synthesize mContentScrollView;

- (IBAction) galleryClickAction
{
    NSLog(@"gallery click aciton !");
    AMOfferGalleryViewController *gallerViewController = [[AMOfferGalleryViewController alloc] initWithNibName:@"AMOfferGalleryViewController" bundle:nil offerDetail:mOfferDetail];
    [self.navigationController pushViewController:gallerViewController animated:YES];
    [gallerViewController release];
}

- (NSString *) getBizType : (NSString *)typeCode
{
    if(typeCode !=nil){
        if([typeCode isEqualToString:BIZ_TYPE_INVESTMENT]){
            return @"生产加工";
        }else if([typeCode isEqualToString:BIZ_TYPE_MANUFACTURER]){
            return @"经销批发";
        }else if([typeCode isEqualToString:BIZ_TYPE_TRADE]){
            return @"招商代理";
        }else if([typeCode isEqualToString:BIZ_TYPE_WHOLESALE]){
            return @"商业服务";
        }else{
            return @"其他";
        }
        
    }
           
    return nil;
}

- (NSString *) getNoNilString:(NSString *) str
{
    return str != nil? str:@"";
}
            
- (NSString *) getAddressString:(AMAddress *)address
{
    if(address != nil){
        NSString * provinceName = [self getNoNilString:[address provinceName]];
        NSString * areaName = [self getNoNilString:[address areaName]];
//        NSString * streetName = [self getNoNilString:[address streetAddress]];
        
        if([StringUtils getIndexOf:provinceName inFather:areaName] >=0){
//            return [areaName stringByAppendingString:streetName];
            return areaName;

        }else{
//            return [[provinceName stringByAppendingString:areaName] stringByAppendingString:streetName];
             return [provinceName stringByAppendingString:areaName];
        }
    }else{
        return nil;
    }
}

- (void) setOfferDetail:(AMOfferDetail *)offerDetail
{
    if(mOfferDetail != nil)
        [mOfferDetail release];
    mOfferDetail = [offerDetail retain];
    
    [self setContentData];
}

- (NSMutableArray *) getOfferImageUrlArray
{
    NSMutableArray * array = [[[NSMutableArray alloc] init] autorelease];
    if(mOfferDetail !=nil 
       && mOfferDetail.imageList != nil 
       && mOfferDetail.imageList.count > 0){
        int size = mOfferDetail.imageList.count;
        for(int i=0; i<size;i++){
            NSString * url = [NSURL URLWithString:[((AMImage *)[mOfferDetail.imageList objectAtIndex:i]) convertSize150x150ImageURI]];
            [array addObject:url];
        }
        
    }
    
    return array;
}

- (void) viewWillAppear:(BOOL)animated
{
    [super viewWillDisappear:animated];
    
    [AMLogUtils appendLog:APP_PRD_DETAL_FOUR];
    
    if (isTalkAfterWwLogin) {
        [[NSNotificationCenter defaultCenter] removeObserver:self];
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(onWwLoginSucc) name:NOTIFICATION_WW_LOGIN_SUCC object:nil];
    }
}

- (void)viewWillDisappear:(BOOL)animated {
  	[super viewWillDisappear:animated];
    
    [[NSNotificationCenter defaultCenter] removeObserver:self];
}

- (void)didReceiveMemoryWarning
{
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    // Release any cached data, images, etc that aren't in use.
}

- (void) setContentData {
    
}

#pragma mark - View lifecycle

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    isTalkAfterWwLogin = NO;
    
    mOfferDetail = [self.dataDict objectForKey:TAB_VIEW_DATA_OFFER_DETAIL];
    [self setContentDataEx];
}

-(void) setContentDataEx
{
    int tempY = 0;
    
    if(mOfferDetail != nil){
        AliSmallRemoteImageGallery * gallery = [[AliSmallRemoteImageGallery alloc] init];
        gallery.delegate = self;
        [gallery setImageUrls:[self getOfferImageUrlArray]];
        
        [self.mContentScrollView addSubview:gallery];
        tempY += (gallery.frame.size.height + 10);
        [gallery release];
    }
    
    //设置subject
    if(mOfferDetail.subject != nil){
        UILabel *subjectLabel =  [[self getSubjectLabel:mOfferDetail.subject] retain];
        subjectLabel.frame = CGRectMake(15, tempY, subjectLabel.frame.size.width, subjectLabel.frame.size.height);
        [self.mContentScrollView addSubview:subjectLabel];
        tempY +=subjectLabel.frame.size.height +10;
        [subjectLabel release];
    }
    
    NSMutableArray * keyValueArray = [[NSMutableArray alloc] init ];

    
    //设置pricelist
    if(mOfferDetail.priceRange != nil
       && mOfferDetail.priceRange.count > 0
       && mOfferDetail.productUnit != nil){
        AliPriceRangeView * priceListView = [[AliPriceRangeView alloc ] init ];
        priceListView.paddingTop = 0;
        priceListView.paddingBottom = 0;
        [priceListView setPriceRangeArray:mOfferDetail.priceRange productUnit:mOfferDetail.productUnit];
        
        KeyValueObject * obj = [[KeyValueObject alloc] init];
        obj.type = VALUE_STYLE_MULTI_HORIZONTAL;
        obj.key = @"价格";
        
        NSMutableArray * valueArray = [[NSMutableArray alloc] init];
        [valueArray addObject: priceListView];

        obj.value = valueArray;
        [valueArray release];
        
        [keyValueArray addObject:obj];
        [obj release];

//        priceListView.frame = CGRectMake(0, tempY, 320, priceListView.frame.size.height);
//        [self.mContentScrollView addSubview:priceListView];
//        tempY += priceListView.frame.size.height + 10;
        [priceListView release];
    }
    
    KeyValueObject *lineDividedObj;
//    lineDividedObj.type = ITEM_STYLE_LINE_DIVIDED;
//    [keyValueArray addObject:lineDividedObj];
//    [lineDividedObj release];
    
//    //供货总量
//    if(mOfferDetail.amount != nil 
//       && mOfferDetail.amount.floatValue > 0 
//       && mOfferDetail.productUnit != nil){
//        
//        KeyValueObject * obj = [[KeyValueObject alloc] init];
//        obj.key = @"供货总量";
//        obj.value =  [mOfferDetail.amount.stringValue stringByAppendingString: mOfferDetail.productUnit];
//        [keyValueArray addObject:obj];
//        [obj release];
// 
//    }
    
    //经营类型
    if (mOfferDetail.companyBrief != nil 
        && mOfferDetail.companyBrief.bizType != nil ) {
        
        KeyValueObject * obj = [[KeyValueObject alloc] init];
        obj.key = @"生产加工";
        obj.value =  [self getBizType:mOfferDetail.companyBrief.bizType];
        [keyValueArray addObject:obj];
        [obj release];
        
    }
    
    //发货地址
    NSString * addressStr;
    if (mOfferDetail.sendAddress != nil){
        if((addressStr = [self getAddressString:mOfferDetail.sendAddress]) != nil){
            KeyValueObject * obj = [[KeyValueObject alloc] init];
            obj.key = @"发货地";
            obj.value =  addressStr;
            [keyValueArray addObject:obj];
            [obj release];
    
        }
    }
    
    //供货支持
    if(mOfferDetail.priceRange!=nil 
       && mOfferDetail.priceRange.count>0 
       && [mOfferDetail.priceRange objectAtIndex:0] != nil 
       && ((AMPrice *)[mOfferDetail.priceRange objectAtIndex:0]).beginAmount > 0
       && mOfferDetail.productUnit != nil){
        
        KeyValueObject * obj = [[KeyValueObject alloc] init];
        obj.type = VALUE_STYLE_MULTI_HORIZONTAL;
        obj.key = @"供货支持";
        
        NSMutableArray * valueArray = [[NSMutableArray alloc] init];
        [valueArray addObject: [[((AMPrice *)[mOfferDetail.priceRange objectAtIndex:0]).beginAmount.stringValue stringByAppendingString:mOfferDetail.productUnit] stringByAppendingString:@"起批"]];
        if(mOfferDetail.mixWholeSale.boolValue == YES){
            [valueArray addObject:[[AliImageControlFactory sharedInstance] getImageButtonWithType:MIXED_BUY_ICON] ];
        }
        obj.value = valueArray;
        [valueArray release];
        
        [keyValueArray addObject:obj];
        [obj release];
    }
    
    //可售数量 
    if(mOfferDetail.availableAmount != nil 
       && mOfferDetail.availableAmount.floatValue > 0 
       && mOfferDetail.productUnit != nil){
        
        KeyValueObject * obj = [[KeyValueObject alloc] init];
        obj.key = @"可售数量";
        obj.value =  [mOfferDetail.availableAmount.stringValue stringByAppendingString:mOfferDetail.productUnit];
        [keyValueArray addObject:obj];
        [obj release];
        
    }
    
    //累计出售
    if(mOfferDetail.dealedAmount!= nil 
       && mOfferDetail.dealedAmount.floatValue >0 
       && mOfferDetail.productUnit != nil){
        
        KeyValueObject * obj = [[KeyValueObject alloc] init];
        obj.key = @"累计出售";
        obj.value =  [mOfferDetail.dealedAmount.stringValue stringByAppendingString:mOfferDetail.productUnit];
        [keyValueArray addObject:obj];
        [obj release];
        
    }
    
    //评价
    if(mOfferDetail.rate != nil 
       && mOfferDetail.rate.averageStarLevel.floatValue > 0){
        
        KeyValueObject * obj = [[KeyValueObject alloc] init];
        obj.type = VALUE_STYLE_MULTI_HORIZONTAL;
        obj.key = @"商品满意度";
        
        NSMutableArray * valueArray = [[NSMutableArray alloc] init];
        
        AliSatisfyRateView * satisfyView = [[AliSatisfyRateView alloc] init];
        [satisfyView setSatisfyRateIvs:mOfferDetail.rate.averageStarLevel.floatValue];
        [valueArray addObject: satisfyView];
        [satisfyView release];
        
        if(mOfferDetail.rate.remarkCount.intValue >=0){
            UILabel * commentLabel = [[UILabel alloc] init];
            commentLabel.backgroundColor = [UIColor clearColor];
            commentLabel.font = [UIFont systemFontOfSize:12.0f];
            commentLabel.textColor = [UIHelp colorWithHexString:@"0xA8A8A8"];
            commentLabel.text = [[@"(共" stringByAppendingString:mOfferDetail.rate.remarkCount.stringValue] stringByAppendingString:@"条评价)"];
            [commentLabel sizeToFit];
            
            [valueArray addObject:commentLabel];
            [commentLabel release];
//            [valueArray addObject:[[@"(共" stringByAppendingString:mOfferDetail.rate.remarkCount.stringValue] stringByAppendingString:@"条评价)"]];
        }
        
        obj.value = valueArray;
        [valueArray release];
        
        [keyValueArray addObject:obj];
        [obj release];
    }
    
    lineDividedObj = [[KeyValueObject alloc] init];
    lineDividedObj.type = ITEM_STYLE_LINE_DIVIDED;
    [keyValueArray addObject:lineDividedObj];
    [lineDividedObj release];
    

    KeyValueObject * obj = [[KeyValueObject alloc] init];
    obj.type = VALUE_STYLE_MULTI_HORIZONTAL;
    obj.key = @"保障服务";
    NSMutableArray * valueArray = [[NSMutableArray alloc] init];
    if(mOfferDetail.companyBrief != nil){
       if(mOfferDetail.companyBrief.memberType != nil
            && ![mOfferDetail.companyBrief.memberType isEqualToString:MEMBER_TYPE_FREE] ){ 

           //去掉旧的保障标识
//           UIImageView * chengbaoIv = [[UIImageView alloc] init ];
//           chengbaoIv.backgroundColor = [UIColor clearColor];
//           chengbaoIv.image = [UIImage imageNamed:@"icon_b"];
//           [chengbaoIv sizeToFit];
//        
//           [valueArray addObject:chengbaoIv];
//           [chengbaoIv release];
        
        
           UIImageView * moneyIv = [[UIImageView alloc] init ];
           moneyIv.backgroundColor = [UIColor clearColor];
           moneyIv.image = [UIImage imageNamed:@"icon_y"];
           [moneyIv sizeToFit];
        
           [valueArray addObject:moneyIv];
           [moneyIv release];
       }else{
           //解决当没有保障协议字距错位的问题
           UIImageView * moneyIv = [[UIImageView alloc] init ];
           moneyIv.backgroundColor = [UIColor clearColor];
           [moneyIv sizeToFit];
           
           [valueArray addObject:moneyIv];
           [moneyIv release];
       }
        
        if(mOfferDetail.companyBrief.creditBase != nil){
            if(mOfferDetail.companyBrief.creditBase.realPrice != nil
               && mOfferDetail.companyBrief.creditBase.realPrice.boolValue == YES){
                UIImageView * baojiaIv = [[UIImageView alloc] init ];
                baojiaIv.backgroundColor = [UIColor clearColor];
                baojiaIv.image = [UIImage imageNamed:@"icon_j"];
                [baojiaIv sizeToFit];
                
                [valueArray addObject:baojiaIv];
                [baojiaIv release];
            }
            
            if(mOfferDetail.companyBrief.creditBase.fastpay != nil
               && mOfferDetail.companyBrief.creditBase.fastpay.boolValue == YES){
                UIImageView * fastpayIv = [[UIImageView alloc] init ];
                fastpayIv.backgroundColor = [UIColor clearColor];
                fastpayIv.image = [UIImage imageNamed:@"icon_q"];
                [fastpayIv sizeToFit];
                
                [valueArray addObject:fastpayIv];
                [fastpayIv release];
            }
            
            if(mOfferDetail.companyBrief.creditBase.fastpay != nil
               && mOfferDetail.companyBrief.creditBase.fastpay.boolValue == YES){
                UIImageView * shidiIv = [[UIImageView alloc] init ];
                shidiIv.backgroundColor = [UIColor clearColor];
                shidiIv.image = [UIImage imageNamed:@"icon_s"];
                [shidiIv sizeToFit];
                
                [valueArray addObject:shidiIv];
                [shidiIv release];
            }
            
        }
    }
    
    obj.value = valueArray;
    [valueArray release];
    
    [keyValueArray addObject:obj];
    [obj release];
    
    //支付宝
    if(mOfferDetail.tradeInfo != nil
       && mOfferDetail.tradeInfo.assureEnable.boolValue == YES){
        
        KeyValueObject * obj = [[KeyValueObject alloc] init];
        obj.type = VALUE_STYLE_MULTI_HORIZONTAL;
        obj.key = @"付款方式";
        
        NSMutableArray * valueArray = [[NSMutableArray alloc] init];
//        [valueArray addObject: [[AliImageControlFactory sharedInstance] getImageButtonWithType:ALI_PAY_ICON] ]; 去掉盾牌图标
        [valueArray addObject:@"支付宝担保交易"];
        obj.value = valueArray;
        [valueArray release];
        
        [keyValueArray addObject:obj];
        [obj release];
    }
    
    lineDividedObj = [[KeyValueObject alloc] init];
    lineDividedObj.type = ITEM_STYLE_LINE_DIVIDED;
    [keyValueArray addObject:lineDividedObj];
    [lineDividedObj release];
    
    if(mOfferDetail != nil
       && mOfferDetail.companyBrief != nil ){
        
        AliMemberContactView * contactView = [[AliMemberContactView alloc] init];
        contactView.memberContactDelegate = self;
        [contactView setNavigationController:self.navigationController];
        
        [contactView setContactInfo:mOfferDetail.companyBrief memberId:mOfferDetail.memberId];
        [contactView reloadData];
        
        KeyValueObject * obj = [[KeyValueObject alloc] init];
        obj.type = ITEM_STYLE_CUSTOME;
        obj.key = @"";
        obj.value = contactView;
        
        [keyValueArray addObject:obj];
        [obj release];
        
        [contactView release];
    }
    

    AliKeyValueMapView * mappingView = [[AliKeyValueMapView alloc] init];
    mappingView.paddingTop = 0;
    [mappingView setContentArray:keyValueArray maxKeyLabelString:@"五个汉子宽"];
    mappingView.frame = CGRectMake(0, tempY, 320, mappingView.frame.size.height);
    
    [self.mContentScrollView addSubview:mappingView];
    tempY += mappingView.frame.size.height;
    [mappingView release];
    [keyValueArray release];
    
    self.mContentScrollView.contentSize = CGSizeMake(320, tempY);
}

-(UILabel *) getSubjectLabel:(NSString *)subject
{
    UILabel * subjectLabel = [[[UILabel alloc] init]autorelease];
    subjectLabel.backgroundColor = [UIColor clearColor];
    subjectLabel.textColor = [UIHelp colorWithHexString:@"0x000000"];
    subjectLabel.textAlignment = UITextAlignmentLeft;
    subjectLabel.font = [UIFont boldSystemFontOfSize:16.0f];
    subjectLabel.lineBreakMode = UILineBreakModeWordWrap;
    subjectLabel.numberOfLines = 0;
    subjectLabel.text = subject;
    
    subjectLabel.frame = CGRectMake(0, 0, 290, [UIHelp getLabelSizeWithFont:subjectLabel.font labelString:subjectLabel.text labelWidth:290].height);
    
    return subjectLabel;
}

- (void) onWwLoginSucc {
    if (isTalkAfterWwLogin) {
        [self enterTalk];
        isTalkAfterWwLogin = NO;
    }
}

- (void) enterTalk {
    if (mOfferDetail && mOfferDetail.companyBrief.person.name) {
        AMIMTalkViewController * talkViewController = [[AMIMTalkViewController alloc] initWithParam:NO:NO:nil:mOfferDetail.companyBrief.person.wwCode : mOfferDetail.companyBrief.person.name];
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

- (void)viewDidUnload 
{
    [super viewDidUnload];
}

-(void) dealloc
{
    [[NSNotificationCenter defaultCenter] removeObserver:self];
    [mContentScrollView release];
    [mOfferDetail release];
    [super dealloc];
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    // Return YES for supported orientations
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
    //return YES;
}

@end
