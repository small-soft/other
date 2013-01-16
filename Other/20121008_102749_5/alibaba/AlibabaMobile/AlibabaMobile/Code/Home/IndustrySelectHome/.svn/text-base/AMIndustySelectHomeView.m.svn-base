//
//  AMIndustySelectHomeView.m
//  AlibabaMobile
//
//  Created by cloud ma on 12-9-4.
//  Copyright (c) 2012年 alibaba. All rights reserved.
//

#import "AMIndustySelectHomeView.h"
#import "AMIndustrySelectHomeCell.h"
#import "AMActivityDetailViewController.h"
#import "UserDataUtils.h"

@interface AMIndustySelectHomeView ()

@property (nonatomic,retain) NSArray *sourceData;
@end

@implementation AMIndustySelectHomeView
@synthesize headerView = _headerView;
@synthesize tableView = _tableView;
@synthesize sourceData = _sourceData;
@synthesize delegate = _delegate;


+(id)createView
{
    NSArray *nib = [[NSBundle mainBundle] loadNibNamed:@"AMIndustySelectHomeView" 
                                                 owner:self options:nil];
    for (id oneObject in nib)
    {
        if ([oneObject isKindOfClass:[AMIndustySelectHomeView class]])
        {
            AMIndustySelectHomeView *obj = (AMIndustySelectHomeView *)oneObject;
            [obj initView];
            return obj;
        }
    }
    return nil;
}

- (id)initView
{
    if (self) {
        // Initialization code
        
        NSInteger industrySelectNumber = [UserDataUtils getSelectNumber];
       
        //    if(YES){
        if(industrySelectNumber == 0){
            self.headerView.hidden = NO;  
            self.tableView.frame = CGRectMake( self.headerView.frame.origin.x, self.headerView.frame.origin.y + self.headerView.frame.size.height, self.tableView.frame.size.width, self.frame.size.height - self.headerView.frame.size.height);
        }
        else {
            self.headerView.hidden = YES;
            self.tableView.frame = CGRectMake( self.frame.origin.x, self.frame.origin.y, self.tableView.frame.size.width, self.frame.size.height);

        }

    }
    return self;
}

-(void) dealloc{
    [_sourceData release];
    [_headerView release];
    [_tableView release];
    
    [super dealloc];
}

#pragma mark setMethod
-(NSArray*)sourceData
{
    if (!_sourceData) {
        _sourceData = [[NSArray alloc]initWithObjects:
                       [NSDictionary dictionaryWithObjectsAndKeys:@"服装服饰", @"type",@"女装\\男装\\童装\\箱包\\配饰\\鞋\\运动等", @"introduce",@"hangxuan_picture1", @"typeImage",nil],
                       [NSDictionary dictionaryWithObjectsAndKeys:@"小商品", @"type",@"玩具\\3C数码及礼品\\工艺品\\饰品\\办公文化用品\\汽车用品等", @"introduce",@"hangxuan_picture2", @"typeImage",nil],
                       [NSDictionary dictionaryWithObjectsAndKeys:@"家居百货", @"type",@"家庭装修\\家用电器\\美容护肤\\日用百货\\母婴用品\\食品饮料等", @"introduce", @"hangxuan_picture3", @"typeImage",nil],
                       [NSDictionary dictionaryWithObjectsAndKeys:@"工业品", @"type",@"机械设备和仪器\\零部件\\电子元器件\\五金工具\\安防等用于工业生产的产品", @"introduce",@"hangxuan_picture4", @"typeImage",nil],
                       [NSDictionary dictionaryWithObjectsAndKeys:@"原材料", @"type",@"化工\\冶金\\橡塑\\农林\\纺织和能源行业生产的原材料及其制品", @"introduce",@"hangxuan_picture5", @"typeImage",nil],
                       nil ];
    }
    return _sourceData;
}

#pragma mark table Delegate method
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section{
    
    return [self.sourceData count];
}


- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath{
    
    
    
    NSUInteger row = [indexPath row];
    AMIndustrySelectHomeCell *cell = (AMIndustrySelectHomeCell *)[tableView dequeueReusableCellWithIdentifier: [AMIndustrySelectHomeCell cellIdentifer]];
    
    if (cell == nil){
        cell = [AMIndustrySelectHomeCell createCell];  
    }
    
    
    NSDictionary *dictMapValues = [_sourceData objectAtIndex:row];
    cell.typeLabel.text =[dictMapValues objectForKey:@"type"];
    cell.introduceLabel.numberOfLines = 2;
    cell.introduceLabel.lineBreakMode = UILineBreakModeCharacterWrap;
    cell.introduceLabel.text = [dictMapValues objectForKey:@"introduce"];
    cell.bkImage.image = [UIImage imageNamed:[dictMapValues objectForKey:@"typeImage"] ];
    cell.bkImage.contentMode = YES;
    cell.bkImage.frame = CGRectMake(22, 0, 82, 82);
    cell.upTypeImage.frame = CGRectMake(61, 0, 4, 8);
    cell.bottomTypeImage.frame = CGRectMake(61, 78, 4, 8);
    cell.buttomSeparateImage.frame = CGRectMake(65, 82, 256, 1);
    
    if(row==0){
        cell.upTypeImage.hidden = YES;
    }else{
        cell.upTypeImage.hidden = NO;
        
    }
    if(row==[_sourceData count]-1){
        cell.bottomTypeImage.hidden = YES;
        cell.buttomSeparateImage.hidden= YES;
    }else{
        cell.bottomTypeImage.hidden = NO;
        cell.buttomSeparateImage.hidden= NO;
    }
    return cell;
    
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath{
    
    return 83.;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath{
    
    [UserDataUtils setSelectNumber:[indexPath row]];
    [UserDataUtils setNavigationHomeBar:NO];//用于判断是否是由tabbar进入首页，这里主要是用于修复在下拉菜单下点击tabbar出现的bug
    [[NSNotificationCenter defaultCenter] postNotificationName:NOTIFICATION_CHANGE_HOME object:nil];
    switch ([indexPath row]) {
        case 0:
            [AMLogUtils appendLog:INDUSTRIAL_DROP_DOWN_BUTTON_ONE];
            break;
        case 1:
            [AMLogUtils appendLog:INDUSTRIAL_DROP_DOWN_BUTTON_TWO];
            break;
        case 2:
            [AMLogUtils appendLog:INDUSTRIAL_DROP_DOWN_BUTTON_THREE];
            break;
        case 3:
            [AMLogUtils appendLog:INDUSTRIAL_DROP_DOWN_BUTTON_FOUR];
            break;
        case 4:
            [AMLogUtils appendLog:INDUSTRIAL_DROP_DOWN_BUTTON_FIVE];
            break;
        default:
            break;
    }
//    [self.delegate showTableView];
//    self.alpha = 0.0;
    [tableView deselectRowAtIndexPath:indexPath animated:NO];
    
}


/*
// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect
{
    // Drawing code
}
*/

@end
