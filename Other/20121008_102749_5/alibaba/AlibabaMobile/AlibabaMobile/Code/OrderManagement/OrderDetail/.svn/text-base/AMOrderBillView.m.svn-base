//
//  AMOrderBillView.m
//  AlibabaMobile
//
//  Created by lei.jul on 12-7-20.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMOrderBillView.h"
#import "KeyValueObject.h"
#import "SystemUtils.h"
#import "AliKeyValueCellForInvoice.h"
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

@implementation AMOrderBillView

@synthesize contactArray = _contactArray;

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
        
        self.sectionFooterHeight = 0;
        self.sectionHeaderHeight = 0;
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
    
    _contactArray = [[NSMutableArray alloc] init];
    if(data != nil && data.orderModel != nil){
        
        //购货单位名称
        if(data.orderModel!=nil  ){
            
            KeyValueObject *obj = [[KeyValueObject alloc] init];
            
            obj.key = @"购货单位名称：";
            obj.value = data.orderModel.orderInvoiceModel.invoiceCompanyName;
            if (obj.value == nil || [obj.value isEqualToString:@""]) {
                obj.value = @"无";
            }
            obj.type = TYPE_OTHER;
            
            [_contactArray addObject:obj];
            [obj release];
        }
        
        //纳税人识别码
        if(data.orderModel!=nil ){
            KeyValueObject *obj = [[KeyValueObject alloc] init];
            
            obj.key = @"纳税人识别码：";
            obj.value =  data.orderModel.orderInvoiceModel.taxpayerIdentify;
            obj.value = data.orderModel.orderInvoiceModel.invoiceCompanyName;
            if (obj.value == nil || [obj.value isEqualToString:@""]) {
                obj.value = @"无";
            }
            obj.type = TYPE_OTHER;
            
            [_contactArray addObject:obj];
            [obj release];
        }
        
        //开户行及账号
        if(data.orderModel!=nil ){
            KeyValueObject *obj = [[KeyValueObject alloc] init];
            
            obj.key = @"开户行及账号：";
            obj.value =  data.orderModel.orderInvoiceModel.bankAndAccount;
            obj.value = data.orderModel.orderInvoiceModel.invoiceCompanyName;
            if (obj.value == nil || [obj.value isEqualToString:@""]) {
                obj.value = @"无";
            }
            obj.type = TYPE_OTHER;
            
            [_contactArray addObject:obj];
            [obj release];
        }
        
        //收取发票电话
        if(data.orderModel!=nil ){
            KeyValueObject *obj = [[KeyValueObject alloc] init];
            
            obj.key = @"收取联系电话：";
            obj.value =  data.orderModel.orderInvoiceModel.receivePhone;
            obj.value = data.orderModel.orderInvoiceModel.invoiceCompanyName;
            if (obj.value == nil || [obj.value isEqualToString:@""]) {
                obj.value = @"无";
            }
            obj.type = TYPE_PHONE;
            
            [_contactArray addObject:obj];
            [obj release];
        }
        
        //收取发票地址
        if(data.orderModel!=nil ){
            KeyValueObject *obj = [[KeyValueObject alloc] init];
            
            obj.key = @"收取发票地址：";
            obj.value =  data.orderModel.orderInvoiceModel.receiveAddress;
            
//            obj.value =  @"aaaaaaaaaaaaaaaaaaaaaaaaabbbbbbbbbbbbbbccccccccccccccccccccccddddddddddddddddddddddddeeeeeeeeeeeeeeeeeee";
            obj.value = data.orderModel.orderInvoiceModel.invoiceCompanyName;
            if (obj.value == nil || [obj.value isEqualToString:@""]) {
                obj.value = @"无";
            }
            obj.type = TYPE_OTHER;
            
            [_contactArray addObject:obj];
            [obj release];
        }
        
    }
    CGSize size = [data.orderModel.orderInvoiceModel.receiveAddress sizeWithFont:[UIFont  systemFontOfSize:14.0f] constrainedToSize:CGSizeMake(129,MAXFLOAT)];
    
//    CGSize size = [@"aaaaaaaaaaaaaaaaaaaaaaaaabbbbbbbbbbbbbbccccccccccccccccccccccddddddddddddddddddddddddeeeeeeeeeeeeeeeeeee" sizeWithFont:[UIFont  systemFontOfSize:14.0f] constrainedToSize:CGSizeMake(129,MAXFLOAT)];
    
    
    
    self.frame = CGRectMake(self.frame.origin.x, self.frame.origin.y, self.frame.size.width, DEFAULT_ROW_HEIGHT*_contactArray.count  + 1  );
    
    if (size.height != 0) {
        self.frame = CGRectMake(self.frame.origin.x, self.frame.origin.y, self.frame.size.width, DEFAULT_ROW_HEIGHT*_contactArray.count  +1 + size.height - DEFAULT_ROW_HEIGHT );
    }
    
//     NSLog(@"objvalue 3:%@; size height:%f",@"aaaaaaaaaaaaaaaaaaaaaaaaabbbbbbbbbbbbbbccccccccccccccccccccccddddddddddddddddddddddddeeeeeeeeeeeeeeeeeee",size.height);
    
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
            
            
        default:
            break;
    }
    
    [self deselectRowAtIndexPath:indexPath animated:NO];
} 

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    if ([indexPath row] == 4 ) {
        KeyValueObject * obj = [_contactArray objectAtIndex: [indexPath row]];
        
        
        
        if (obj.value == nil) {
            obj.value = @"无"; 
        }
        
        
        
        CGSize size = [obj.value sizeWithFont:[UIFont  systemFontOfSize:14.0f] constrainedToSize:CGSizeMake(129,MAXFLOAT)];
        
        
        NSLog(@"objvalue 1:%@; size height:%f",obj.value,size.height);
        
        if (size.height > DEFAULT_ROW_HEIGHT) {
            return  size.height;
        }
        
        
    }
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
    
    AliKeyValueCellForInvoice *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];  
    if (cell == nil) {  
        NSArray *nib = [[NSBundle mainBundle] loadNibNamed:@"AliKeyValueCellForInvoice" 
                                                     owner:self options:nil];
        for (id oneObject in nib)
            if ([oneObject isKindOfClass:[AliKeyValueCellForInvoice class]])
                cell = (AliKeyValueCellForInvoice *)oneObject; 
        
        cell.selectionStyle = UITableViewCellSelectionStyleGray; 
        
    }  
    
    KeyValueObject * obj = [_contactArray objectAtIndex: [indexPath row]];
    NSString * title  = obj.key;
    NSString * value = obj.value;
    int type = obj.type;
    
    cell.keyLabel.text = title;
    cell.valueLabel.text = value;
    
    if ([indexPath row] == 4) {
        cell.valueLabel.text = value;
        cell.valueLabel.numberOfLines = 0;
        cell.valueLabel.lineBreakMode = UILineBreakModeCharacterWrap;
        cell.valueLabel.backgroundColor = [UIColor clearColor];
//        cell.valueLabel.frame = CGRectMake(115, 11, 129, 100);
        cell.valueLabel.font = [UIFont  systemFontOfSize:14.0f];
        CGSize size = [cell.valueLabel.text sizeWithFont:cell.valueLabel.font constrainedToSize:CGSizeMake(129,MAXFLOAT)];
        
        cell.valueLabel.frame = CGRectMake(115, 11, 129, size.height);
        
        NSLog(@"objvalue 2:%@; size height:%f",cell.valueLabel.text,size.height);
    }
    
    //    cell.lineBreakMode = NO;
    
    if(type != TYPE_FAX && type != TYPE_WANGWANG){
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
            cell.seceptorImageView.hidden = YES;
            //  cell.iconImageView.image = [UIImage imageNamed:@"icon_aliww"];
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


@end
