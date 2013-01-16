//
//  AMOrderProtocolView.m
//  AlibabaMobile
//
//  Created by lei.jul on 12-10-11.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMOrderProtocolView.h"



#import "KeyValueObject.h"
#import "SystemUtils.h"
#import "AliKeyValueCell.h"
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


@implementation AMOrderProtocolView

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
        
        self.sectionHeaderHeight = 0;
        self.sectionFooterHeight = 0;
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
        
        //保障金额
        if(data.orderModel!=nil  ){
            
            KeyValueObject *obj = [[KeyValueObject alloc] init];
            
            obj.key = @"保障金额：";
            obj.value = [NSString stringWithFormat:@"￥%d", data.orderModel.orderProtocalModel.ensurePayment];
            obj.type = TYPE_OTHER;
            
            [_contactArray addObject:obj];
            [obj release];
        }
        
        //保障期限
        if(data.orderModel!=nil ){
            KeyValueObject *obj = [[KeyValueObject alloc] init];
            
            NSDate *nd = [NSDate  dateWithTimeIntervalSince1970: [data.orderModel.orderProtocalModel.gmtDeadline doubleValue]/1000 ];//时间需要除以1000
            NSDateFormatter *dateFormat = [[NSDateFormatter alloc] init];
            [dateFormat setDateFormat:@"yyyy-MM-dd HH:mm:ss"];
            NSString *dateString = [dateFormat stringFromDate:nd];
            [dateFormat release];

            
            obj.key = @"保障截至：";
            obj.value = dateString;
            obj.type = TYPE_OTHER;
            
            [_contactArray addObject:obj];
            [obj release];
         }
        
    }
    self.frame = CGRectMake(self.frame.origin.x, self.frame.origin.y, self.frame.size.width, DEFAULT_ROW_HEIGHT*_contactArray.count+1);
    
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
    
    AliKeyValueCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];  
    if (cell == nil) {  
        NSArray *nib = [[NSBundle mainBundle] loadNibNamed:@"AliKeyValueCell" 
                                                     owner:self options:nil];
        for (id oneObject in nib)
            if ([oneObject isKindOfClass:[AliKeyValueCell class]])
                cell = (AliKeyValueCell *)oneObject; 
        
        cell.selectionStyle = UITableViewCellSelectionStyleGray; 
        
    }  
    
    KeyValueObject * obj = [_contactArray objectAtIndex: [indexPath row]];
    NSString * title  = obj.key;
    NSString * value = obj.value;
    int type = obj.type;
    
    cell.keyLabel.text = title;
    cell.valueLabel.text = value;
    
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
