//
//  AMBuyerSellerInfoView.m
//  AlibabaMobile
//
//  Created by lei.jul on 12-7-23.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMBuyerSellerInfoView.h"

#import "KeyValueObject.h"
#import "SystemUtils.h"
#import "AliKeyValueCellForBuyerSeller.h"
#import "AMLogUtils.h"
#import "Utils.h"
#import "UIHelp.h"


static const int TYPE_WANGWANG = 0;
static const int TYPE_PHONE = 1;
static const int TYPE_MOBILE_PHONE = 2;
static const int TYPE_FAX = 3;
static const int TYPE_HOMEPAGE = 4;
static const int TYPE_COMPANY_DETAIL = 5;
static const int TYPE_EMAIL = 6;

static const int TYPE_OTHER = 9;

static const int DEFAULT_ROW_HEIGHT = 44;


@implementation AMBuyerSellerInfoView

@synthesize contactArray = _contactArray;

@synthesize memberContactDelegate=_memberContactDelegate;

-(void)dealloc
{
    
    [_contactArray release];
    _contactArray = nil;
    [_navigationController release];
    _navigationController = nil;
    [super dealloc];
}

- (id)init
{
    [super initWithFrame:CGRectMake(0, 0, 320, 10) style:UITableViewStyleGrouped];
    if(self){
        _contactArray = nil;
        _navigationController = nil;
        self.delegate  = self;
        self.dataSource = self;
        self.bounces = NO;
        self.scrollEnabled = NO;
        self.backgroundColor = [UIColor clearColor];
        
        self.sectionHeaderHeight = 0;
        self.sectionFooterHeight = 0 ;
    }
    return self;
}

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        self.frame = frame;
    }
    return self;
}

-(void) setData:(AMOrderDetailResult *)data withMemberId:(NSString *)memberId
{
    BOOL isBuyer = [memberId isEqualToString:data.orderModel.buyerMemberId];

    
    _contactArray = [[NSMutableArray alloc] init];
    if(data != nil && data.orderModel != nil){
        
        //买家/卖家
        if (isBuyer) {
            //卖家
            if(data.orderModel.sellerCompanyName!=nil && ![data.orderModel.sellerCompanyName isEqualToString:@""] ){
                
                KeyValueObject *obj = [[KeyValueObject alloc] init];
                
                obj.key = @"卖           家：";
                obj.value = data.orderModel.sellerCompanyName;
                obj.type = TYPE_COMPANY_DETAIL;
                
                [_contactArray addObject:obj];
                [obj release];
            }
            
            //会员登录名
            if(data.orderModel.sellerMemberId!=nil && ![data.orderModel.sellerMemberId isEqualToString:@""] ){
                
                KeyValueObject *obj = [[KeyValueObject alloc] init];
                
                
                obj.key = @"会员登录名：";
                obj.value = data.orderModel.sellerMemberId;
                obj.type = TYPE_WANGWANG;
                
                [_contactArray addObject:obj];
                [obj release];
                
                
            }
            
            
            
            // 支付宝账号
            if(data.orderModel.sellerAlipayLoginId != nil && ![data.orderModel.sellerAlipayLoginId isEqualToString:@""]   ){
                KeyValueObject *obj = [[KeyValueObject alloc] init];
                
                
                obj.key = @"支付宝账号：";
                obj.value = data.orderModel.sellerAlipayLoginId;
                obj.type = TYPE_OTHER;
                
                [_contactArray addObject:obj];
                [obj release];
                
                
            }
        }else {
            //买家
            if(data.orderModel.buyerCompanyName !=nil && ![data.orderModel.buyerCompanyName isEqualToString:@""] ){
                
                KeyValueObject *obj = [[KeyValueObject alloc] init];
                
                obj.key = @"买           家：";
                obj.value = data.orderModel.buyerCompanyName;
                obj.type = TYPE_COMPANY_DETAIL;
                
                [_contactArray addObject:obj];
                [obj release];
                
                
            }
            
            //会员登录名
            if(data.orderModel.buyerMemberId!=nil && ![data.orderModel.buyerMemberId isEqualToString:@""] ){
                
                KeyValueObject *obj = [[KeyValueObject alloc] init];
                
                
                obj.key = @"会员登录名：";
                obj.value = data.orderModel.buyerMemberId;
                obj.type = TYPE_WANGWANG;
                
                [_contactArray addObject:obj];
                [obj release];
                
                
            }
            
            
            
            // 支付宝账号
            if(data.orderModel.buyerAlipayLoginId != nil && ![data.orderModel.buyerAlipayLoginId isEqualToString:@""]   ){
                KeyValueObject *obj = [[KeyValueObject alloc] init];
                
                
                obj.key = @"支付宝账号：";
                obj.value = data.orderModel.buyerAlipayLoginId;
                obj.type = TYPE_OTHER;
                
                [_contactArray addObject:obj];
                [obj release];
                
                
            }
        }
        
        
        
    }
    self.frame = CGRectMake(self.frame.origin.x, self.frame.origin.y, self.frame.size.width, DEFAULT_ROW_HEIGHT*_contactArray.count +1);
    
    
    
    NSLog(@"x,y,w,h: %f,%f,%f,%u",self.frame.origin.x,self.frame.origin.y,self.frame.size.width, DEFAULT_ROW_HEIGHT*_contactArray.count+1);
}

-(void) setNavigationController:(UINavigationController *)controller
{
    if(_navigationController)
        [_navigationController release];
    _navigationController = [controller retain];;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    NSUInteger row = [indexPath row];
    KeyValueObject *obj = [_contactArray objectAtIndex:row];
    int type = obj.type;
    switch (type) {
        case TYPE_WANGWANG:
            if ([self.memberContactDelegate respondsToSelector:@selector(wangWangDidSelected)]) {
                [self.memberContactDelegate wangWangDidSelected];
            }
            break;
        case TYPE_PHONE:{
            [SystemUtils makeCallWithNumber:obj.value];
//            [AMLogUtils appendLog:PRECISION_VISITOR_DETAIL_THREE];
            break;
        }
        case TYPE_MOBILE_PHONE:{
            [SystemUtils makeCallWithNumber:obj.value];
//            [AMLogUtils appendLog:PRECISION_VISITOR_DETAIL_FOUR];
            break;
        }
        case TYPE_FAX:{
            [SystemUtils makeCallWithNumber:obj.value];
            break;
        }
        case TYPE_HOMEPAGE:{
            [SystemUtils openBrowserWithUrl:obj.value];
            break;
        }
        case TYPE_EMAIL:{
//            [AMLogUtils appendLog:PRECISION_VISITOR_DETAIL_FIVE];
            [Utils launchMailApp:obj.value];
            break;
        }
        case TYPE_COMPANY_DETAIL:{
            [self goToCompanyInfo];
            break;
        }
            
        default:
            break;
    }
    
    [self deselectRowAtIndexPath:indexPath animated:NO];
} 


- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    return DEFAULT_ROW_HEIGHT;
}
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    if(_contactArray!= nil){
        NSInteger num =  _contactArray.count;
        
        
        return num ;
    }
    
    return 0;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    static NSString *CellIdentifier = @"Cell";  
    
    AliKeyValueCellForBuyerSeller*cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];  
    if (cell == nil) {  
        NSArray *nib = [[NSBundle mainBundle] loadNibNamed:@"AliKeyValueCellForBuyerSeller" 
                                                     owner:self options:nil];
        for (id oneObject in nib)
            if ([oneObject isKindOfClass:[AliKeyValueCellForBuyerSeller class]])
                cell = (AliKeyValueCellForBuyerSeller *)oneObject; 
        
        cell.selectionStyle = UITableViewCellSelectionStyleGray; 
        
    }  
    
    KeyValueObject * obj = [_contactArray objectAtIndex: [indexPath row]];
    NSString * title  = obj.key;
    NSString * value = obj.value;
    int type = obj.type;
    
    cell.keyLabel.text = title;
    cell.valueLabel.text = value;
    
    //    cell.lineBreakMode = NO;
    
    if(type != TYPE_FAX ){
        //   cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
    }else{
        cell.userInteractionEnabled = NO;
    }
    
    switch (type) {
        case TYPE_COMPANY_DETAIL:
            cell.seceptorImageView.hidden = NO;
            cell.iconImageView.image = [UIImage imageNamed:@"icon_picker_company"];
            break;
        case TYPE_PHONE:
            cell.seceptorImageView.hidden = NO;
            cell.iconImageView.image = [UIImage imageNamed:@"icon_telephone_p"];
            break;
        case TYPE_MOBILE_PHONE:
            cell.seceptorImageView.hidden = NO;
            cell.iconImageView.image = [UIImage imageNamed:@"icon_mobilephone_p"];
            break;
        case TYPE_EMAIL:
            cell.seceptorImageView.hidden = NO;
            cell.iconImageView.image = [UIImage imageNamed:@"icon_message"];
            break;
        case TYPE_FAX:
            cell.seceptorImageView.hidden = YES;
            //  cell.iconImageView.image = [UIImage imageNamed:@"icon_aliww"];
            break;
        case TYPE_WANGWANG:
            cell.seceptorImageView.hidden = NO;
            cell.iconImageView.image = [UIImage imageNamed:@"icon_aliww"];
            break;
        case TYPE_HOMEPAGE:
            cell.seceptorImageView.hidden = YES;
            cell.iconImageView.image = [UIImage imageNamed:@"icon_listarrow"];
            break;
            
        default:
            cell.seceptorImageView.hidden = YES;
            break;
    }
    
    cell.backgroundColor = [UIHelp colorWithHexString:@"0xffffff"];
    
    return cell;  
}





//@synthesize memberContactDelegate;

//- (id)initWithFrame:(CGRect)frame
//{
//    self = [super initWithFrame:frame];
//    if (self) {
//        // Initialization code
//    }
//    return self;
//}
//
//
//-(id) initWithData:(AMOrderDetailResult *)data withMemberId:(NSString*) memberId
//{
//    self = [super init];
//    self.frame = CGRectMake(0, 0, 300, 150);
//    self.backgroundColor = [UIColor clearColor];
//    //    [[self layer] setBorderColor:[[UIColor blackColor] CGColor]];
//    //    [[self layer]setBorderWidth:1.0f];
//    
//    int tempY = 10;
//    
//    //这个逻辑真奇怪。。。
//    BOOL isBuyer = [memberId isEqualToString:data.orderModel.buyerMemberId];
//    
//    UILabel * label1 = [[UILabel alloc] init];
//    if ( isBuyer )
//    {
//        label1.text = @"卖家 ：";
//    }else {
//        label1.text = @"买家 ：";
//    }
//    
//    label1.backgroundColor = [UIColor clearColor];
//    label1.frame = CGRectMake(10, tempY, 150, 20);
//    label1.font = [UIFont  systemFontOfSize:14.0f];
//    [self addSubview:label1];
//    
//    UIButton * buttonComp = [[UIButton alloc]init];
//    [buttonComp setBackgroundImage:[UIImage imageNamed:@"icon_picker_company"] forState:UIControlStateNormal];
//    [buttonComp addTarget:self action:@selector(goToCompanyInfo) forControlEvents:UIControlEventTouchUpInside];
//    buttonComp.frame= CGRectMake(110, tempY, 20, 20   );;
//    
//    [self addSubview:buttonComp];
//
//    
//    UILabel * contentLabel1 = [[UILabel alloc] init];
//    
//    if ( isBuyer )
//    {
//        contentLabel1.text = data.orderModel.sellerCompanyName;
//    }else {
//        contentLabel1.text = data.orderModel.buyerCompanyName;
//    }
//    
//    if (contentLabel1.text == nil || [contentLabel1.text isEqualToString:@""]) {
//        contentLabel1.text = @"无";
//    }
//    
//    contentLabel1.backgroundColor = [UIColor clearColor];
//    contentLabel1.font = [UIFont  systemFontOfSize:14.0f];
//    contentLabel1.lineBreakMode = UILineBreakModeCharacterWrap;
//    contentLabel1.numberOfLines = 0;
//    
//    CGFloat height = [contentLabel1.text sizeWithFont:contentLabel1.font constrainedToSize:CGSizeMake(180, MAXFLOAT)].height;
//    NSLog(@"height:%lf",height);
//    contentLabel1.frame = CGRectMake(110 + 25, tempY, 180 - 25, [contentLabel1.text sizeWithFont:contentLabel1.font constrainedToSize:CGSizeMake(180 - 25, MAXFLOAT)].height);
//    [self addSubview:contentLabel1];
//    
//    tempY += contentLabel1.frame.size.height + 10;
//    [label1 release];
//    [contentLabel1 release];
//    
//    UILabel * label2 = [[UILabel alloc] init];
//    label2.text = @"会员登陆名：";
//    label2.backgroundColor = [UIColor clearColor];
//    label2.frame = CGRectMake(10, tempY, 100, 20);
//    label2.font = [UIFont  systemFontOfSize:14.0f];
//    [self addSubview:label2];
//    
//    
//    UIButton * buttonWW = [[UIButton alloc]init];
//    [buttonWW setBackgroundImage:[UIImage imageNamed:@"icon_aliww"] forState:UIControlStateNormal];
//    [buttonWW addTarget:self action:@selector(goToWangWang) forControlEvents:UIControlEventTouchUpInside];
//    buttonWW.frame= CGRectMake(110, tempY, 20, 20   );;
//    
//    [self addSubview:buttonWW];
//    
//    
//    UILabel * contentLabel2 = [[UILabel alloc] init];
//    
//    contentLabel2.backgroundColor = [UIColor clearColor];
//    contentLabel2.font = [UIFont  systemFontOfSize:14.0f];
//    contentLabel2.lineBreakMode = UILineBreakModeCharacterWrap;
//    contentLabel2.numberOfLines = 0;
//    if ( isBuyer )
//    {
//        contentLabel2.text = data.orderModel.sellerMemberId;
//    }else {
//        contentLabel2.text = data.orderModel.buyerMemberId;
//    }
//    
//    if (contentLabel2.text == nil || [contentLabel2.text isEqualToString:@""]) {
//        contentLabel2.text = @"无";
//    }
//
//    contentLabel2.frame = CGRectMake(110 + 25, tempY, 180 - 25, [contentLabel2.text sizeWithFont:contentLabel2.font constrainedToSize:CGSizeMake(180 - 25, MAXFLOAT)].height);
//    [self addSubview:contentLabel2];
//    tempY += contentLabel2.frame.size.height + 10;
//    [label2 release];
//    [contentLabel2 release];
//    
//    
//    UILabel * label3 = [[UILabel alloc] init];
//    label3.text = @"支付宝账户：";
//    label3.backgroundColor = [UIColor clearColor];
//    label3.frame = CGRectMake(10, tempY, 100, 20);
//    label3.font = [UIFont  systemFontOfSize:14.0f];
//    [self addSubview:label3];
//    
//    UILabel * contentLabel3 = [[UILabel alloc] init];
//    
//
//    contentLabel3.backgroundColor = [UIColor clearColor];
//    contentLabel3.font = [UIFont  systemFontOfSize:14.0f];
//    contentLabel3.lineBreakMode = UILineBreakModeCharacterWrap;
//    contentLabel3.numberOfLines = 0;
//    if ( isBuyer )
//    {
//        contentLabel3.text = data.orderModel.sellerAlipayLoginId;
//    }else {
//        contentLabel3.text = data.orderModel.buyerAlipayLoginId;
//    }
//    if (contentLabel3.text == nil || [contentLabel3.text isEqualToString:@""]) {
//        contentLabel3.text = @"无";
//    }
//
//    contentLabel3.frame = CGRectMake(110 , tempY, 180, [contentLabel3.text sizeWithFont:contentLabel3.font constrainedToSize:CGSizeMake(180, MAXFLOAT)].height);
//    [self addSubview:contentLabel3];
//    tempY += contentLabel3.frame.size.height + 10; 
//    [label3 release];
//    [contentLabel3 release];
//    
//    UILabel * label4 = [[UILabel alloc] init];
//    label4.text = @"买家留言：";
//    label4.backgroundColor = [UIColor clearColor];
//    label4.frame = CGRectMake(10, tempY, 100, 20);
//    label4.font = [UIFont  systemFontOfSize:14.0f];
//    [self addSubview:label4];
//    
//    UILabel * contentLabel4 = [[UILabel alloc] init];
//    
//    
//    contentLabel4.backgroundColor = [UIColor clearColor];
//    contentLabel4.font = [UIFont  systemFontOfSize:14.0f];
//    contentLabel4.lineBreakMode = UILineBreakModeCharacterWrap;
//    contentLabel4.numberOfLines = 0;
//    if (data.orderModel.buyerFeedback == nil || [data.orderModel.buyerFeedback isEqualToString:@""]) {
//        contentLabel4.text = @"无";
//    }else {
//        contentLabel4.text = data.orderModel.buyerFeedback;
//    }
//    
//   
//    contentLabel4.frame = CGRectMake(110 , tempY, 180, [contentLabel4.text sizeWithFont:contentLabel4.font constrainedToSize:CGSizeMake(180, MAXFLOAT)].height);
//    [self addSubview:contentLabel4];
//    tempY += contentLabel4.frame.size.height + 10; 
//    [label4 release];
//    [contentLabel4 release];
//
//    
//    
//    self.frame = CGRectMake(0, 0, 300, tempY);
//    
//    return self;
//
//}

/*
// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect
{
    // Drawing code
}
*/


-(void) goToCompanyInfo
{
    NSLog(@"Go to Company info");

    
    [[NSNotificationCenter defaultCenter] postNotificationName:NOTIFICATION_ORDER_TO_COMPANYDETAIL object:nil];

}
//
//-(void) goToWangWang
//{
//    NSLog(@"Go to ww");
//    
//    if ([self.memberContactDelegate respondsToSelector:@selector(wangWangDidSelected)])
//    {
//        [self.memberContactDelegate wangWangDidSelected];
//    }
//    
//}

@end
