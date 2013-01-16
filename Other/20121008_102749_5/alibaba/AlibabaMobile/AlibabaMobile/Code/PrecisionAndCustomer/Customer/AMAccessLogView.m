//
//  AMAccessLogView.m
//  AlibabaMobile
//
//  Created by lei.jul  on 12-6-28.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMAccessLogView.h"

#import "AliEnqueryCell.h"
#import "AliEnqueryFirstCell.h"



#import "AliPrecisionFirstCell.h"

#import "AliPrecisionCell.h"
#import "AMPrecisionVisitorAccessLog.h"
#import "AMPrecisionVisitorAccessLogDetail.h"

#import "AMPrecisionDetailViewController.h"
#import "UIHelp.h"

@implementation AMAccessLogView

@synthesize accessArray = _accessArray;
@synthesize accessCount = _accessCount;



- (id)init
{
    [super initWithFrame:CGRectMake(0, 0, 200, 10) style:UITableViewStyleGrouped];
//    [super init];
    if(self){
        _accessArray = [[NSMutableArray alloc] init];
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


- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        self.frame = frame;
    }
    return self;
}

-(void) setNavigationController:(UINavigationController *)controller
{
    if(_navigationController)
        [_navigationController release];
    _navigationController = [controller retain];;
}


- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{ 
    
    if ( [indexPath row] == 2 )
    {
        [[NSNotificationCenter defaultCenter] postNotificationName:NOTIFICATION_PRECISION_VIEW_SHOW object:self];
    }
    
    [self deselectRowAtIndexPath:indexPath animated:NO];
}


- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    if(self.accessArray.count == 1)
    {
        return 2;
    }
    
    NSLog(@"count : %d",self.accessCount.intValue);
    return  3;
    
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    if ([indexPath row] == 0)
    {
        return 34;
    }
    if ([indexPath row] == 2)
    {
        return 12;
    }
    if (self.accessArray.count == 0) {
        return 29;
    }
    AMPrecisionVisitorAccessLog *log = (AMPrecisionVisitorAccessLog*)[ self.accessArray objectAtIndex:self.accessArray.count - 1 - ([indexPath row] - 1)];
    
    return (log.logList.count * 48 - 5 + 34);
    
 
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    static NSString *CellIdentifier = @"Cell";  
    static NSString *FirstCellIdentifier = @"AliPrecisionFirstCell";  
    
    UIColor * viewColor = [UIHelp colorWithHexString:@"0xffffff"];
    
//    AliEnqueryCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];  
    AliPrecisionCell  *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier]; 
    AliPrecisionFirstCell *firstCell = [tableView dequeueReusableCellWithIdentifier:FirstCellIdentifier]; 
    if (cell == nil) {  
        NSArray *nib = [[NSBundle mainBundle] loadNibNamed:@"AliPrecisionCell" 
                                                     owner:self options:nil];
        for (id oneObject in nib)
            if ([oneObject isKindOfClass:[AliPrecisionCell class]])
                cell = (AliPrecisionCell *)oneObject; 
        
        cell.selectionStyle = UITableViewCellSelectionStyleGray; 
        
    }  
    
    if (firstCell == nil) {  
        NSArray *nib = [[NSBundle mainBundle] loadNibNamed:@"AliPrecisionFirstCell" 
                                                     owner:self options:nil];
        for (id oneObject in nib)
            if ([oneObject isKindOfClass:[AliPrecisionFirstCell class]])
                firstCell = (AliPrecisionFirstCell *)oneObject; 
        
        firstCell.selectionStyle = UITableViewCellSelectionStyleGray; 
        
    }  
    
    
    if ([indexPath row] == 0) {
        firstCell.count.text =  [NSString stringWithFormat:@"%d",self.accessCount.intValue];
        
        if (self.accessCount.intValue > 100) {
            firstCell.endLabel.frame = CGRectMake(firstCell.endLabel.frame.origin.x + 10 ,firstCell.endLabel.frame.origin.y, firstCell.endLabel.frame.size.width, firstCell.endLabel.frame.size.height);
        }else if (self.accessCount.intValue > 10) {
            firstCell.endLabel.frame = CGRectMake(firstCell.endLabel.frame.origin.x + 5 ,firstCell.endLabel.frame.origin.y, firstCell.endLabel.frame.size.width, firstCell.endLabel.frame.size.height);
        }
        
        firstCell.selectionStyle = UITableViewCellSelectionStyleNone;//设置cell不可点击

        return firstCell;
        
    }else if ([indexPath row] == 2) {
        UITableViewCell * mycell = [[[UITableViewCell alloc]init ] autorelease];
        mycell.backgroundColor = [UIHelp colorWithHexString:@"0xd6d6d6"];
        UIImageView * imageView = [[UIImageView alloc]init ];
        imageView.frame = CGRectMake(154, 3, 9, 6);
        imageView.image = [UIImage imageNamed:@"icon_app_drown"];
        [mycell addSubview:imageView];
        [imageView release];
        mycell.selectionStyle = UITableViewCellSelectionStyleNone;//设置cell不可点击
        return mycell;
        
    }else{
        if (self.accessArray.count == 0) {
            return cell;
        }
        else {
            AMPrecisionVisitorAccessLog *log = (AMPrecisionVisitorAccessLog*)[ self.accessArray objectAtIndex:self.accessArray.count - 1];
            
            UILabel * label = [[UILabel alloc]init];
            label.frame = CGRectMake(20, 10, 260, 14);
            label.text = @"直接访问: ";
            label.font = [UIFont  systemFontOfSize:14.0f];
            label.backgroundColor = viewColor;
            label.text = [label.text stringByAppendingString:log.time];
            
            [cell addSubview:label];
            [label release];
            
            int tempY = 34;
            
            int i = 0;
            for (i = 0 ; i < log.logList.count - 1  ; i ++) {
                AMPrecisionVisitorAccessLogDetail * item =(AMPrecisionVisitorAccessLogDetail*)   [log.logList objectAtIndex:i];
                UILabel * label1 = [[UILabel alloc]init];
                label1.frame = CGRectMake(25, tempY, 260, 14);
                label1.text = item.title;
                label1.font = [UIFont  systemFontOfSize:14.0f];
                label1.textColor = [UIHelp colorWithHexString:@"0x0067ac"];
                label1.backgroundColor = viewColor;
                tempY += 19;
                [cell addSubview:label1];
                [label1 release];
                
                UILabel * label2 = [[UILabel alloc]init];
                label2.frame = CGRectMake(25, tempY, 150, 14);
                label2.font = [UIFont  systemFontOfSize:14.0f];
                label2.textColor = [UIHelp colorWithHexString:@"0x666666"];
                label2.backgroundColor = viewColor;
                label2.text = @"查看:";
                label2.text = [label2.text stringByAppendingFormat:@"%@次",item.browseCount];
                
                [cell addSubview:label2];
                [label2 release];
                
                UILabel * label3 = [[UILabel alloc]init];
                label3.frame = CGRectMake(154, tempY, 150, 14);
                label3.font = [UIFont  systemFontOfSize:14.0f];
                label3.textColor = [UIHelp colorWithHexString:@"0x666666"];
                label3.backgroundColor = viewColor ;
                label3.text = @"停留:";
                label3.text = [label3.text stringByAppendingString:item.stayTime];
                
                [cell addSubview:label3];
                [label3 release];
                
                tempY += 21;
                
                UIImageView * sep = [[UIImageView alloc]init];
                sep.frame = CGRectMake(25, tempY, 270, 2);
                sep.image = [UIImage imageNamed:@"line_bg"];
                [cell addSubview:sep];
                tempY += 8;
                [sep release];
                
            }
            
            AMPrecisionVisitorAccessLogDetail * item =(AMPrecisionVisitorAccessLogDetail*)   [log.logList objectAtIndex:i];
            UILabel * label1 = [[UILabel alloc]init];
            label1.frame = CGRectMake(25, tempY, 260, 14);
            label1.text = item.title;
            label1.font = [UIFont  systemFontOfSize:14.0f];
            label1.textColor = [UIHelp colorWithHexString:@"0x0067ac"];
            label1.backgroundColor = viewColor;
            tempY += 19;
            [cell addSubview:label1];
            [label1 release];
            
            UILabel * label2 = [[UILabel alloc]init];
            label2.frame = CGRectMake(25, tempY, 150, 14);
            label2.font = [UIFont  systemFontOfSize:14.0f];
            label2.textColor = [UIHelp colorWithHexString:@"0x666666"];
            label2.backgroundColor = viewColor;
            label2.text = @"查看:";
            label2.text = [label2.text stringByAppendingFormat:@"%@次",item.browseCount];
            
            [cell addSubview:label2];
            [label2 release];
            
            UILabel * label3 = [[UILabel alloc]init];
            label3.frame = CGRectMake(154, tempY, 150, 14);
            label3.font = [UIFont  systemFontOfSize:14.0f];
            label3.textColor = [UIHelp colorWithHexString:@"0x666666"];
            label3.backgroundColor = viewColor ;
            label3.text = @"停留:";
            label3.text = [label3.text stringByAppendingString:item.stayTime];
            
            [cell addSubview:label3];
            [label3 release];
            
            tempY += 24;
            
            cell.backgroundColor = viewColor;
            cell.selectionStyle = UITableViewCellSelectionStyleNone;//设置cell不可点击
            return cell;
            
        }
        
          
    }
    
    
    return cell;  
}

-(void)calculateHeight
{
     NSLog(@"addObjectsFromArray : %d",self.accessArray.count);
    if (self.accessArray.count == 0) {
        self.frame  =  CGRectMake(0, 0 ,320, 29 + 34 + 12 + 20);
    }
    else if (self.accessArray.count == 1)
    {
        AMPrecisionVisitorAccessLog *log = (AMPrecisionVisitorAccessLog*)[ self.accessArray objectAtIndex:self.accessArray.count - 1];
        
        self.frame  =  CGRectMake(0, 0 ,320, (log.logList.count * 48 - 5 + 34) + 34  + 20);
    }
    else {
        AMPrecisionVisitorAccessLog *log = (AMPrecisionVisitorAccessLog*)[ self.accessArray objectAtIndex:self.accessArray.count - 1];
        
        self.frame  =  CGRectMake(0, 0 ,320, (log.logList.count * 48 - 5 + 34) + 34 + 12 + 20);
    }
    
}

@end
