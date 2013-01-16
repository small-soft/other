//
//  EnqueryView.m
//  AlibabaMobile
//
//  Created by lei.jul on 12-6-13.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.


//询盘列表
//

#import "AMContactView.h"
#import "KeyValueObject.h"
#import "AliKeyValueCell.h"
#import "AMCompanyTabViewController.h"
#import "AMMemberBrief.h"
#import "SystemUtils.h"

#import "AMEnqueryView.h"
#import "AliEnqueryCell.h"
#import "AliEnqueryFirstCell.h"
#import "AMEnqueryItem.h"

#import "AMEnqueryProductItem.h"
#import "UIHelp.h"




@implementation AMEnqueryView

@synthesize enqueryArray = _enqueryArray;
@synthesize enqueryCount = _enqueryCount;

- (id)init
{
    [super initWithFrame:CGRectMake(0, 0, 320, 10) style:UITableViewStyleGrouped];
    if(self){
        _enqueryArray = [[NSMutableArray alloc] init];
        _navigationController = nil;
        self.delegate  = self;
        self.dataSource = self;
        self.bounces = NO;
        self.scrollEnabled = NO
        ;
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

-(void) setEnqueryInfo:(NSArray *)enqueries
{

}

-(void) setNavigationController:(UINavigationController *)controller
{
    if(_navigationController)
        [_navigationController release];
    _navigationController = [controller retain];;
}


- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{ 
    
        
    [self deselectRowAtIndexPath:indexPath animated:NO];
} 

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    if ([indexPath row] == 0)
    {
        return 34;
    }
    return 80;
}
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{

    
    NSLog(@"count : %d",self.enqueryCount.intValue);
    if(self.enqueryCount.intValue >10){
       return 11;
    }else{
       return  self.enqueryCount.intValue + 1 ;  
    }

}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    static NSString *CellIdentifier = @"Cell";  
    static NSString *FirstCellIdentifier = @"AMEnqueryFirstCell";  
    
    AliEnqueryCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];  
    AliEnqueryFirstCell *firstCell = [tableView dequeueReusableCellWithIdentifier:FirstCellIdentifier]; 
    if (cell == nil) {  
        NSArray *nib = [[NSBundle mainBundle] loadNibNamed:@"AliEnqueryCell" 
                                                     owner:self options:nil];
        for (id oneObject in nib)
            if ([oneObject isKindOfClass:[AliEnqueryCell class]])
                cell = (AliEnqueryCell *)oneObject; 
        
        cell.selectionStyle = UITableViewCellSelectionStyleGray; 

    }  
     
    if (firstCell == nil) {  
        
        NSArray *nib = [[NSBundle mainBundle] loadNibNamed:@"AliEnqueryFirstCell" 
                                                     owner:self options:nil];
        for (id oneObject in nib)
            if ([oneObject isKindOfClass:[AliEnqueryFirstCell class]])
                firstCell = (AliEnqueryFirstCell *)oneObject; 
        
        firstCell.selectionStyle = UITableViewCellSelectionStyleGray; 
        
    }  
    
    
    if ([indexPath row] == 0) {
        firstCell.count.text =  [NSString stringWithFormat:@"%d",self.enqueryCount.intValue];
        if (self.enqueryCount.intValue > 100) {
            firstCell.endLabel.frame = CGRectMake(firstCell.endLabel.frame.origin.x + 10 ,firstCell.endLabel.frame.origin.y, firstCell.endLabel.frame.size.width, firstCell.endLabel.frame.size.height);
        }else if (self.enqueryCount.intValue > 10) {
            firstCell.endLabel.frame = CGRectMake(firstCell.endLabel.frame.origin.x + 5 ,firstCell.endLabel.frame.origin.y, firstCell.endLabel.frame.size.width, firstCell.endLabel.frame.size.height);
        }
        return firstCell;
        
    }else {
        
        AMEnqueryItem * item  = (AMEnqueryItem*)[_enqueryArray objectAtIndex: ([indexPath row] - 1)];
        
        
        //询盘时间
        NSLog(@"%lf", item.enquiriesDate.doubleValue);
        NSLog(@"%d", item.intent.intValue);
  
        
        NSDate *nd = [NSDate  dateWithTimeIntervalSince1970: [item.enquiriesDate doubleValue]/1000 ];//时间需要除以1000
        
        NSDateFormatter *dateFormat = [[NSDateFormatter alloc] init];
        [dateFormat setDateFormat:@"【yyyy-MM-dd HH:mm】"];
        NSString *dateString = [dateFormat stringFromDate:nd];
        NSLog(@"date: %@", dateString);
        [dateFormat release]; 
        
        cell.label1.text = dateString;
//        cell.label2.text = [item.enquiriesSource stringByAppendingString:@")"];
        
        //询盘来源
        cell.label2.text = [[AMEnqueryView getEnquerySource:item.enquiriesSource ] stringByAppendingString:@")"];
        
        //意向度
        cell.label3.text = [ AMEnqueryView getEnqueryIntent:item.intent  ];
      
        
        //意向商品，如果有取第一项
        if (item.productItems!= nil && item.productItems.count > 0)
        {
            AMEnqueryProductItem  * product = [item.productItems objectAtIndex:0 ];
            cell.label4.text = [NSString stringWithFormat:@"%@", product.productName];
            
        }
        
        
        //询盘进展
        cell.label5.text =  [AMEnqueryView getEnqueryStatus:item.status] ;
        
        cell.backgroundColor = [UIHelp colorWithHexString:@"0xffffff"];
        
    }
    

    
    cell.selectionStyle = UITableViewCellSelectionStyleNone;//设置cell不可点击
    return cell;  
}

+(NSString* ) getEnquerySource:(NSString*) source
{
    if ([source isEqualToString:@"1"] || [source isEqualToString:@"9"]) {
        return @"网站";
    }
    else if ([source isEqualToString:@"2"] ) {
        return @"留言";
    }
    else if ([source isEqualToString:@"3"] || [source isEqualToString:@"6"]) {
        return @"精准营销";
    }
    else if ([source isEqualToString:@"0"] || [source isEqualToString:@"4"]) {
        return @"手工生成";
    }
    else if ([source isEqualToString:@"5"] ) {
        return @"旺旺";
    }
    else if ([source isEqualToString:@"7"] ) {
        return @"营销推广";
    }
    else if ([source isEqualToString:@"8"] ) {
        return @"买家推荐";
    }
    else {
        return @"";
    }
    
}

+(NSString* ) getEnqueryIntent:(NSString*) intent
{
    if ( [intent isEqualToString:@"3"] )
    {
        return @"高";
    }
    else if ( [intent isEqualToString:@"2"] )
    {
        return @"中";
    }
    else if ( [intent isEqualToString:@"1"] )
    {
        return @"低";
    }
    else{
        return @"";
    }
}

+(NSString* ) getEnqueryStatus:(NSString*) status
{
    
    if ( [status isEqualToString:@"0"] )
    {
        return @"还没谈";
    }
    else if ( [status isEqualToString:@"1"] )
    {
        return @"正在谈";
    }
    else if ( [status isEqualToString:@"2"] )
    {
        return @"谈成了";
    }
    else if ( [status isEqualToString:@"3"] )
    {
        return @"没希望了";
    }
    else{
        return @"";
    }

}

-(void)dealloc
{

    [_enqueryArray release];
    [_navigationController release];
    [super dealloc];
}

@end
