//
//  AliMemberContactView.m
//  AlibabaMobile
//
//  Created by  on 12-2-13.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AliMemberContactView.h"
#import "KeyValueObject.h"
#import "AliKeyValueCell.h"
#import "AMCompanyTabViewController.h"
#import "AMMemberBrief.h"
#import "SystemUtils.h"

static const int TYPE_WANGWANG = 0;
static const int TYPE_PHONE = 1;
static const int TYPE_MOBILE_PHONE = 2;
static const int TYPE_FAX = 3;
static const int TYPE_HOMEPAGE = 4;
static const int TYPE_COMPANY_DETAIL = 5;
static const int TYPE_OTHER = 9;

static const int DEFAULT_ROW_HEIGHT = 43;

@interface AliMemberContactView()
{
    UINavigationController * _navigationController;
    AMMemberBrief * _memberBrief;
    NSString * _memberId;
}

@property (nonatomic, retain) NSMutableArray * contactArray;
@end

@implementation AliMemberContactView

@synthesize contactArray = _contactArray;
@synthesize memberContactDelegate = _memberContactDelegate;

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

- (id) initWithFrame:(CGRect)frame
{
    [super init];
    if(self){
        self.frame = frame;
    }
    return self;
}

-(void) setContactInfo:(AMMemberBrief *)brief memberId:(NSString *)memberId
{
    _memberBrief = [brief retain];
    _memberId = [memberId retain];
    _contactArray = [[NSMutableArray alloc] init];
    if(_memberBrief != nil){
        //公司名称呢过
        if(_memberBrief.name != nil){
            KeyValueObject *obj = [[KeyValueObject alloc] init];
            obj.key = @"公司名称：";
            obj.value = _memberBrief.name;
            obj.type = TYPE_COMPANY_DETAIL;
            [_contactArray addObject:obj];
            [obj release];
        }
        
        //联系人  
        //职位可能为nil，两种显示
        //gender 1为先生，-1为女士
        if(_memberBrief.person != nil){
            KeyValueObject *obj = [[KeyValueObject alloc] init];
            obj.key = @"联  系 人：";
            if(!_memberBrief.person.jobTitle){
                _memberBrief.person.jobTitle = @"";
                obj.value = [NSString stringWithFormat:@"%@ %@%@",_memberBrief.person.name ,(_memberBrief.person.gender.intValue == 1?@"先生":@"女士"), _memberBrief.person.jobTitle];
                if(_memberBrief.person != nil
                   && _memberBrief.person.wwCode != nil && ![_memberBrief.person.wwCode isEqualToString:@""]
                   )
                {
                    obj.type = TYPE_WANGWANG;
                }else {
                    obj.type = TYPE_OTHER;
                }
                [_contactArray addObject:obj];
                [obj release];
            }else{
                obj.value = [NSString stringWithFormat:@"%@ %@(%@)",_memberBrief.person.name ,(_memberBrief.person.gender.intValue == 1?@"先生":@"女士"), _memberBrief.person.jobTitle];
                if(_memberBrief.person != nil
                   && _memberBrief.person.wwCode != nil && ![_memberBrief.person.wwCode isEqualToString:@""]
                   )
                {
                    obj.type = TYPE_WANGWANG;
                }else {
                    obj.type = TYPE_OTHER;
                }
                [_contactArray addObject:obj];
                [obj release];
            }
        }
 
        //电话
        if(_memberBrief.contact!=nil 
           && _memberBrief.contact.phone != nil
           && _memberBrief.contact.phone.count > 0){
            
            int size = _memberBrief.contact.phone.count;
            for(int i=0;i<size; i++){
                KeyValueObject *obj = [[KeyValueObject alloc] init];

                if(i == 0){
                    obj.key = @"电       话：";
                }else{
                    obj.key = @"";
                }
                obj.value = ((NSString *)[_memberBrief.contact.phone objectAtIndex:i]);
                obj.type = TYPE_PHONE;
                
                [_contactArray addObject:obj];
                [obj release];
            }
            
        }
        
        //手机
        if(_memberBrief.contact != nil
           && _memberBrief.contact.mobile != nil
           && _memberBrief.contact.mobile.count >0){
            
            int size = _memberBrief.contact.mobile.count;
            for(int i=0; i<size;i++){
                KeyValueObject *obj = [[KeyValueObject alloc] init];
                if(i == 0){
                    obj.key = @"移动电话：";
                }else{
                    obj.key = @"";
                }    
                obj.value = ((NSString *)[_memberBrief.contact.mobile objectAtIndex:i]);
                obj.type = TYPE_MOBILE_PHONE;
                
                [_contactArray addObject:obj];
                [obj release];
            }
            
        }
        
        //传真
        if(_memberBrief.contact != nil
           && _memberBrief.contact.fax != nil){
            KeyValueObject *obj = [[KeyValueObject alloc] init];
            obj.key = @"传       真：";
            obj.value = _memberBrief.contact.fax;
            obj.type = TYPE_FAX;
            [_contactArray addObject:obj];
            [obj release];
           
        }
        
        
        //主页
        if(_memberBrief.contact != nil
           && _memberBrief.contact.homepage != nil
           && _memberBrief.contact.homepage.count >0){
            
            int size = _memberBrief.contact.homepage.count;
            for(int i=0; i<size;i++){
                KeyValueObject *obj = [[KeyValueObject alloc] init];
                if(i == 0){
                    obj.key = @"主       页：";
                }else{
                    obj.key = @"";
                }
                obj.value = ((NSString *)[_memberBrief.contact.homepage objectAtIndex:i]);
                obj.type = TYPE_HOMEPAGE;
                
                [_contactArray addObject:obj];
                [obj release];
            }
        }
        
        //旺旺
//        if(_memberBrief.person != nil
//           && _memberBrief.person.wwCode != nil && ![_memberBrief.person.wwCode isEqualToString:@""]
//        ){
//            
//            int size = _memberBrief.contact.homepage.count;
//            for(int i=0; i<size;i++){
//                KeyValueObject *obj = [[KeyValueObject alloc] init];
//                if(i == 0){
//                    obj.key = @"旺       旺：";
//                }else{
//                    obj.key = @"";
//                }
//                obj.value = ((NSString *)_memberBrief.person.wwCode);
//                obj.type = TYPE_WANGWANG;
//                
//                [_contactArray addObject:obj];
//                [obj release];
//            }
//        }

    }
    self.frame = CGRectMake(self.frame.origin.x, self.frame.origin.y, self.frame.size.width, DEFAULT_ROW_HEIGHT*_contactArray.count+25);

}

-(void) setNavigationController:(UINavigationController *)controller
{
    if(_navigationController)
        [_navigationController release];
    _navigationController = [controller retain];;
}


- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{ 
    
    NSUInteger row = [indexPath row];
    KeyValueObject *obj = [_contactArray objectAtIndex:row];
    int type = obj.type;
    switch (type) {
        case TYPE_COMPANY_DETAIL:{
            if(_memberId){
                AMCompanyTabViewController * offerView = [[AMCompanyTabViewController alloc] initWithMemberId:_memberId companyName:_memberBrief.name preViewName:nil];
                if(_navigationController)
                    [_navigationController pushViewController:offerView animated:YES];
                [offerView release];
            }
            
            break;
        }
        case TYPE_WANGWANG:{
            if ([self.memberContactDelegate respondsToSelector:@selector(wangWangDidSelected)]) {
                [self.memberContactDelegate wangWangDidSelected];
            }
        }
            break;
        case TYPE_PHONE:{
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
        case TYPE_OTHER:
            break;
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
        case TYPE_OTHER:
            cell.seceptorImageView.hidden = YES;
            break;    
        default:
            break;
    }
    
    return cell;  
}

-(void)dealloc
{
    [_memberId release];
    [_memberBrief release];
    [_contactArray release];
    [_navigationController release];
    [super dealloc];
}

@end
