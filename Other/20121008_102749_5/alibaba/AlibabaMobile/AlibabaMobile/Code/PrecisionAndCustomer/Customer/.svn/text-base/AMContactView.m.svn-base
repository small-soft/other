//
//  ContactView.m
//  AlibabaMobile
//
//  Created by lei.jul  on 12-2-13.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMContactView.h"
#import "KeyValueObject.h"
#import "AliKeyValueCell.h"
#import "AMCompanyTabViewController.h"
#import "AMMemberBrief.h"
#import "SystemUtils.h"
#import "Utils.h"
#import "UIHelp.h"
#import "AMLogUtils.h"
#import "AMLogTypeCode.h"
#import "AMCustomerInfoMapViewController.h"
#import "AliToastView.h"

static const int TYPE_WANGWANG = 0;
static const int TYPE_PHONE = 1;
static const int TYPE_MOBILE_PHONE = 2;
static const int TYPE_FAX = 3;
static const int TYPE_HOMEPAGE = 4;
static const int TYPE_COMPANY_DETAIL = 5;
static const int TYPE_EMAIL = 6;
static const int TYPE_ADDRESS = 7;



static const int TYPE_OTHER = 9;

static const int DEFAULT_ROW_HEIGHT = 44;

@interface AMContactView()
{
    UINavigationController * _navigationController;
    
}

@property (nonatomic, retain) NSMutableArray * contactArray;

@property (nonatomic, retain) AMCustomerInfo *targetInfo;

@end

@implementation AMContactView

@synthesize contactArray = _contactArray;
@synthesize targetInfo = _targetInfo;

-(void)dealloc
{
    
    [_contactArray release];
    [_navigationController release];
    [_targetInfo release];
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
    }
    return self;
}

-(void) setNavigationController:(UINavigationController *)controller
{
    if(_navigationController)
        [_navigationController release];
    _navigationController = [controller retain];;
}

- (id) initWithFrame:(CGRect)frame
{
    [super init];
    if(self){
        self.frame = frame;
    }
    return self;
}

-(void) setContactInfo:(AMCustomerInfo *)info
{
    if(info){
        self.targetInfo = info;
    }
    
    _contactArray = [[NSMutableArray alloc] init];
    if(info != nil){
        //公司名称
        //        if(info.corpName != nil){
        //            KeyValueObject *obj = [[KeyValueObject alloc] init];
        //            obj.key = @"公司名称：";
        //            obj.value = info.corpName;
        //            obj.type = TYPE_COMPANY_DETAIL;
        //            [_contactArray addObject:obj];
        //            [obj release];
        //
        //        }
        
        
        //电话
        if((info.phoneNumber!=nil || info.mobile!=nil)&& ![info.phoneNumber isEqualToString:@""] ){
            
            KeyValueObject *obj = [[KeyValueObject alloc] init];
            
            
            obj.key = @"电       话：";
            
            if ( info.mobile != nil )
            {
                obj.value = info.mobile;
            }
            else {
                obj.value = info.phoneNumber;
                
            }
            obj.type = TYPE_PHONE;
            
            [_contactArray addObject:obj];
            [obj release];
            
            
        }
        
        //传真
        if(info.faxNumber!=nil&& ![info.faxNumber isEqualToString:@""]  ){
            
            KeyValueObject *obj = [[KeyValueObject alloc] init];
            
            
            obj.key = @"传       真：";
            
            obj.value = [[info.faxCountry stringByAppendingFormat:@" %@", info.faxArea] stringByAppendingFormat:@" %@",info.faxNumber];
            
            obj.type = TYPE_OTHER;
            
            [_contactArray addObject:obj];
            [obj release];
            
            
        }
        
        
        
        // 邮箱
        if(info.email != nil && ![info.email isEqualToString:@""]){
            KeyValueObject *obj = [[KeyValueObject alloc] init];
            
            
            obj.key = @"邮       箱：";
            
            obj.value = info.email;
            obj.type = TYPE_EMAIL;
            
            [_contactArray addObject:obj];
            [obj release];
            
            
        }
        
        // 地址
        if(info.address != nil && ![info.address isEqualToString:@""]){
            
            KeyValueObject *obj = [[KeyValueObject alloc] init];
            
            
            obj.key = @"地       址：";
            
            obj.value = info.address;
            obj.type = TYPE_ADDRESS;
            
            [_contactArray addObject:obj];
            [obj release];
            
            
        }
        
        //邮编
        if(info.postalCode != nil && ![info.postalCode isEqualToString:@""]){
            
            KeyValueObject *obj = [[KeyValueObject alloc] init];
            
            
            obj.key = @"邮       编：";
            
            obj.value = info.postalCode;
            obj.type = TYPE_OTHER;
            
            [_contactArray addObject:obj];
            [obj release];
            
            
        }
        
        
    }
    self.frame = CGRectMake(self.frame.origin.x, self.frame.origin.y, self.frame.size.width, DEFAULT_ROW_HEIGHT*_contactArray.count+25);
    
}




- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{ 
    
    NSUInteger row = [indexPath row];
    KeyValueObject *obj = [_contactArray objectAtIndex:row];
    int type = obj.type;
    switch (type) {
            //        case TYPE_COMPANY_DETAIL:{
            //            if(_memberId){
            //                AMCompanyTabViewController * offerView = [[AMCompanyTabViewController alloc] initWithMemberId:_memberId companyName:_memberBrief.name preViewName:nil];
            //                if(_navigationController)
            //                    [_navigationController pushViewController:offerView animated:YES];
            //            }
            //            
            //            break;
            //        }
        case TYPE_WANGWANG:
            break;
        case TYPE_PHONE:{
            [AMLogUtils appendLog:CUSTOMERMANAGER_CUSTOMERINFO_TWO];//拨打电话
            [SystemUtils makeCallWithNumber:obj.value];
            
            break;
        }
        case TYPE_MOBILE_PHONE:{
            [SystemUtils makeCallWithNumber:obj.value];
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
            [AMLogUtils appendLog:CUSTOMERMANAGER_CUSTOMERINFO_FOUR];
            [Utils launchMailApp:obj.value];
            break;
        }
        case TYPE_ADDRESS:{
            [AMLogUtils appendLog:CUSTOMERMANAGER_CUSTOMERINFO_THREE];
            NSLog(@"customer info address is clicked...");
            
//            AMCustomerInfoMapViewController *mapController = [[[AMCustomerInfoMapViewController alloc] initWithNibName:@"AMCustomerInfoMapViewController" bundle:nil] autorelease];
//            mapController.targetCompanyName = _targetInfo.corpName;
//            mapController.targetCompanyAddress = _targetInfo.address;
//            mapController.targetLatitude = [_targetInfo.latitude doubleValue];;
//            mapController.targetLongitude = [_targetInfo.longitude doubleValue];
//            
//            if(_navigationController){
//                if(mapController.targetCompanyName!=nil&&mapController.targetCompanyAddress!=nil){
//                    mapController.hidesBottomBarWhenPushed=YES;
//                    [_navigationController pushViewController:mapController animated:YES];  
//                }
//            }
            
            [self launchMapController];
            break;
        }
        default:
            break;
    }
    
    [self deselectRowAtIndexPath:indexPath animated:NO];
} 

- (void) launchMapController{
    AMCustomerInfoMapViewController *mapController = [[[AMCustomerInfoMapViewController alloc] initWithNibName:@"AMCustomerInfoMapViewController" bundle:nil] autorelease];
    mapController.targetCompanyName = _targetInfo.corpName;
    mapController.targetCompanyAddress = _targetInfo.address;
    mapController.targetLatitude = [_targetInfo.latitude doubleValue];;
    mapController.targetLongitude = [_targetInfo.longitude doubleValue];
    
    if(_navigationController){
        if(mapController.targetLatitude==0&&mapController.targetLongitude==0){
            [[AliToastView MakeToastWithType:TOAST_STYLE_FAIL info:@"用户地图信息不全!"] show];

        }else{
            mapController.hidesBottomBarWhenPushed=YES;
            [_navigationController pushViewController:mapController animated:YES]; 
        }
    }
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
    
    AliKeyValueCell*cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];  
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
        case TYPE_EMAIL:
            cell.seceptorImageView.hidden = NO;
            cell.iconImageView.image = [UIImage imageNamed:@"icon_message"];
            break;
        case TYPE_ADDRESS:
            cell.seceptorImageView.hidden = NO;
//            cell.iconImageView.frame = CGRectMake(280, 20, 20,20);
            cell.iconImageView.image = [UIImage imageNamed:@"icon_address_xp_p"];
            break;
        default:
            cell.seceptorImageView.hidden = YES;
            break;
    }
    
    cell.backgroundColor = [UIHelp colorWithHexString:@"0xffffff"];
    
    return cell;  
}



@end
