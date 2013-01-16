//
//  IndustrySelectHomeViewController.m
//  AlibabaMobile
//
//  Created by alimobile on 12-8-21.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMIndustrySelectHomeViewController.h"

#import "AMIndustrySelectHomeCell.h"
#import "AMActivityDetailViewController.h"
#import "UserDataUtils.h"

@interface AMIndustrySelectHomeViewController ()

@property (nonatomic,retain) NSArray *sourceData;
@end

@implementation AMIndustrySelectHomeViewController
@synthesize headerView = _headerView;
@synthesize tableView = _tableView;
@synthesize myNavigationBar = _myNavigationBar;
@synthesize myNavigationItem = _myNavigationItem;
@synthesize industrySelectPickView =_industrySelectPickView;
@synthesize sourceData = _sourceData;

-(void) dealloc{
    [_sourceData release];
    [_headerView release];
    [_tableView release];
    [_myNavigationBar release];
    [_myNavigationItem release];
    [_industrySelectPickView release];
    [super dealloc];
}

- (void)viewDidUnload
{
    [_sourceData release];
    _sourceData = nil;
    self.headerView = nil;
    self.tableView = nil;
    self.myNavigationBar = nil;
    self.myNavigationItem = nil;
    self.industrySelectPickView = nil;
    [super viewDidUnload];
}

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

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

- (void)viewDidLoad
{
    [super viewDidLoad];
    // Do any additional setup after loading the view from its nib.
    NSInteger industrySelectNumber = [UserDataUtils getSelectNumber];
    //BOOL firstLaunch = [UserDataUtils getFirstLaunch];
//    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
//    NSNumber *industrySelectNumberForUer = [defaults objectForKey:@"industrySelectNumber"];
    self.tabBarController.tabBar.hidden = YES;
    self.myNavigationBar.backgroundColor = [UIColor colorWithRed:255/255.0f green:115/255.0f blue:0/255.0f alpha:1.0f];
    self.industrySelectPickView = [[AMIndustrySelectPickView alloc] initWithFrame:CGRectMake(0,0, 100, 30)];
    self.industrySelectPickView.delegate = self;
    self.myNavigationItem.titleView = self.industrySelectPickView;
    [self.industrySelectPickView sizeToFit];
    [self.view addSubview:self.myNavigationBar];
//    if(YES){
    if(industrySelectNumber == 0){
        self.myNavigationBar.hidden = YES;
        self.headerView.hidden = NO;  
        self.tableView.frame = CGRectMake( self.headerView.frame.origin.x, self.headerView.frame.origin.y + self.headerView.frame.size.height, self.tableView.frame.size.width, self.view.frame.size.height - self.headerView.frame.size.height);
    }
    else {
        self.myNavigationBar.hidden = NO;
        self.headerView.hidden = YES;
        self.tableView.frame = CGRectMake( self.myNavigationBar.frame.origin.x, self.myNavigationBar.frame.origin.y + self.myNavigationBar.frame.size.height, self.tableView.frame.size.width, self.view.frame.size.height - self.myNavigationBar.frame.size.height);
        
        industrySelectName = [[self.sourceData objectAtIndex:industrySelectNumber-1] objectForKey:@"type"];
    }
    
    
    
    
//    [self.navigationController setNavigationBarHidden:YES animated:NO];

}

- (void)viewWillAppear:(BOOL)animated{
    
//为了便于调试，navi暂时设置为可见
    if (industrySelectName) {
        self.industrySelectPickView.lableTitle.text = [NSString stringWithFormat:industrySelectName];
    }
    
    [self.navigationController setNavigationBarHidden:YES animated:NO];
    [super viewWillAppear:animated];
}

- (void)viewWillDisappear:(BOOL)animated
{
//为了便于调试，navi暂时设置为可见
    [super viewWillDisappear:animated];
    [self.navigationController setNavigationBarHidden:NO animated:NO];
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}

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
//    cell.bkImage.frame = CGRectMake(10, 13, cell.bkImage.image.size.width*0.7, cell.bkImage.image.size.height*0.7);
    
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
    
    return [AMIndustrySelectHomeCell cellHeight];
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath{
    
    [UserDataUtils setSelectNumber:[indexPath row]];
    [[NSNotificationCenter defaultCenter] postNotificationName:NOTIFICATION_CHANGE_HOME object:nil];
    [self industrySelectPickViewEvent];
//    AMActivityDetailViewController *controller = [[AMActivityDetailViewController alloc] initWithNibName:@"AMActivityDetailViewController" bundle:nil];
//    controller.hidesBottomBarWhenPushed=YES;
//    [self.navigationController pushViewController:controller animated:YES];
//    [controller release];
    switch ([indexPath row]) {
        case 0:
            [AMLogUtils appendLog:INDUSTRIAL_PAGE_ONE];
            break;
        case 1:
            [AMLogUtils appendLog:INDUSTRIAL_PAGE_TWO];
            break;
        case 2:
            [AMLogUtils appendLog:INDUSTRIAL_PAGE_THREE];
            break;
        case 3:
            [AMLogUtils appendLog:INDUSTRIAL_PAGE_FOUR];
            break;
        case 4:
            [AMLogUtils appendLog:INDUSTRIAL_PAGE_FIVE];
            break;
        default:
            break;
    }
    [tableView deselectRowAtIndexPath:indexPath animated:NO];
    
}

-(void)industrySelectPickViewEvent
{
    int index= [[self.navigationController viewControllers] indexOfObject:self];
    if (index > 0  ) {
        [self.navigationController setNavigationBarHidden:NO animated:NO];
        
        [self.navigationController popViewControllerAnimated:NO];
    }
    
}


@end
