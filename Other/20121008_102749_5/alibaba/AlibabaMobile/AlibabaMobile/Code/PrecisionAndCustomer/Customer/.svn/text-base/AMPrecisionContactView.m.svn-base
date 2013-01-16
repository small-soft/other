//
//  AMPrecisionContactView.m
//  AlibabaMobile
//
//  Created by alimobile on 12-6-28.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMPrecisionContactView.h"
#import "KeyValueObject.h"
#import "SystemUtils.h"
#import "AliKeyValueCell.h"
#import "AMLogUtils.h"
#import "AMPrecisionDetailViewController.h"
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


@interface AMPrecisionContactView()
{
    UINavigationController * _navigationController;
    
}

@property (nonatomic, retain) NSMutableArray * contactArray;

@end

@implementation AMPrecisionContactView

@synthesize contactArray = _contactArray;


-(void)dealloc
{
    
    [_contactArray release];
    [_navigationController release];
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

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
         self.frame = frame;
    }
    return self;
}

-(void) setContactInfo:(AMPrecisionVisitorDetailResult *)info
{
    
    _contactArray = [[NSMutableArray alloc] init];
    if(info != nil){
      
        //电话
        if(info.corpName!=nil && ![info.corpName isEqualToString:@""] ){
            
            KeyValueObject *obj = [[KeyValueObject alloc] init];
            
            obj.key = @"公司信息：";
            obj.value = info.corpName;
            obj.type = TYPE_OTHER;
            
            [_contactArray addObject:obj];
            [obj release];
            
            
        }
        
        //主营产品
        if(info.mainProduct!=nil && ![info.mainProduct isEqualToString:@""] ){
            
            KeyValueObject *obj = [[KeyValueObject alloc] init];
            
            
            obj.key = @"主营产品：";
            obj.value = info.mainProduct;
            obj.type = TYPE_OTHER;
            
            [_contactArray addObject:obj];
            [obj release];
            
            
        }
        
        
        
        // 主营行业
        if(info.mainBiz != nil && ![info.mainBiz isEqualToString:@""]   ){
            KeyValueObject *obj = [[KeyValueObject alloc] init];
            
            
            obj.key = @"主营行业：";
            obj.value = info.mainBiz;
            obj.type = TYPE_OTHER;
            
            [_contactArray addObject:obj];
            [obj release];
            
            
        }
        
        // 电话
        if(info.fixedPhone != nil && ![info.fixedPhone isEqualToString:@""] ){
            
            KeyValueObject *obj = [[KeyValueObject alloc] init];
            
            
            obj.key = @"电       话：";
            obj.value = info.fixedPhone;
            obj.type = TYPE_PHONE;
            
            [_contactArray addObject:obj];
            [obj release];
            
            
        }
        
        //手机
        if(info.mobilephone != nil && ![info.mobilephone isEqualToString:@""] ){
            
            KeyValueObject *obj = [[KeyValueObject alloc] init];
            
            
            obj.key = @"手       机：";
            
            obj.value = info.mobilephone;
            obj.type = TYPE_MOBILE_PHONE;
            
            [_contactArray addObject:obj];
            [obj release];
            
            
        }
        
        //邮箱
        if(info.email != nil && ![info.email isEqualToString:@""] ){
            
            KeyValueObject *obj = [[KeyValueObject alloc] init];
            
            
            obj.key = @"邮       箱：";
            
            obj.value = info.email;
            obj.type = TYPE_EMAIL;
            
            [_contactArray addObject:obj];
            [obj release];
        }
    }
    self.frame = CGRectMake(self.frame.origin.x, self.frame.origin.y, self.frame.size.width, DEFAULT_ROW_HEIGHT*_contactArray.count+25);
    
    NSLog(@"x,y,w,h: %f,%f,%f,%u",self.frame.origin.x,self.frame.origin.y,self.frame.size.width, DEFAULT_ROW_HEIGHT*_contactArray.count+25);
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
            [AMLogUtils appendLog:PRECISION_VISITOR_DETAIL_THREE];
            break;
        }
        case TYPE_MOBILE_PHONE:{
            [SystemUtils makeCallWithNumber:obj.value];
            [AMLogUtils appendLog:PRECISION_VISITOR_DETAIL_FOUR];
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
            [AMLogUtils appendLog:PRECISION_VISITOR_DETAIL_FIVE];
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
