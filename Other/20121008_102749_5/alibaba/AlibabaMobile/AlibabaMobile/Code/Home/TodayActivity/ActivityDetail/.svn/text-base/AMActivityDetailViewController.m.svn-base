//
//  AMActivityDetailViewController.m
//  AlibabaMobile
//
//  Created by alimobile on 12-8-24.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMActivityDetailViewController.h"

#import "AMActivityDetailCell.h"
#import "AMActivityMutiDetailViewController.h"
#import "AliImageButton.h"
#import "AliImageControlFactory.h"
#import "AMSpecialPriceOffer.h"
#import "HJObjManager.h"
#import "AMTodayActivityBlockBoxCell.h"
#import "AMTodayActivityBlockBoxCell.h"
#import "AliToastView.h"
#import "AMOfferTabViewController.h"
#import "ConstDef.h"
#import "AMLogUtils.h"
#import "AMMoreLoadingView.h"
#import "AMErrorMessageView.h"

#define RGB(r, g, b) [UIColor colorWithRed:r/255.0 green:g/255.0 blue:b/255.0 alpha:1.0]


@interface AMActivityDetailViewController ()

@property (nonatomic,retain) NSArray *sourceData;
@property (nonatomic, retain) NSMutableArray * contentData;
@property (nonatomic, retain) HJObjManager *objMan;

@end

@implementation AMActivityDetailViewController

@synthesize sourceData = _sourceData;
@synthesize displayModel = _displayModel;
@synthesize mTableView = _mTableView;
@synthesize topicOfferRequest = _topicOfferRequest;
@synthesize specialPriceOfferRequest = _specialPriceOfferRequest;
@synthesize contentData = _contentData;
@synthesize objMan = _objMan;
@synthesize activityId = _activityId;
@synthesize activityTitle = _activityTitle;
@synthesize totalCount = _totalCount;
@synthesize isLoading = _isLoading;
@synthesize currentPageIndex = _currentPageIndex;
@synthesize offerPosition = _offerPosition;
@synthesize businessType = _businessType;
@synthesize industryId = _industryId;
@synthesize switchBtn = _switchBtn;
@synthesize timer = _timer;
//@synthesize lastSwitchTime = _lastSwitchTime;
-(void) dealloc{
    
    [_sourceData release];
    [_mTableView release];
    [_topicOfferRequest release];
    [_contentData release];
    [_objMan release];
    [_specialPriceOfferRequest release];
    [_activityId release];
    [_activityTitle release];
    [_industryId release];
    [_switchBtn release];
    [_timer release];
    
    [super dealloc];
}

- (void)viewDidUnload
{
    [_sourceData release];
    _sourceData = nil;
    self.objMan = nil;
    [_contentData release];
    _contentData = nil;
//    [_mLoadingView release];
//    _mLoadingView = nil;
    [super viewDidUnload];
}

-(void)objManInit
{
    _objMan = [[HJObjManager alloc] initWithLoadingBufferSize:6 memCacheSize:20];
    
    NSString* cacheDirectory = [NSHomeDirectory() stringByAppendingString:@"/Library/Caches/activityimgcache/"] ;
	HJMOFileCache* fileCache = [[[HJMOFileCache alloc] initWithRootPath:cacheDirectory] autorelease];
	_objMan.fileCache = fileCache;
    // Have the file cache trim itself down to a size & age limit, so it doesn't grow forever
	fileCache.fileCountLimit = 100;
	fileCache.fileAgeLimit = 60*60*24*7; //1 week
	[fileCache trimCacheUsingBackgroundThread];
    
}

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {

    }
    return self;
}

-(NSMutableArray*)contentData
{
    if (!_contentData) {
        _contentData = [[NSMutableArray alloc]init];
    }
    return _contentData;
}

-(AMTopicOfferRequest*)topicOfferRequest
{
    if (!_topicOfferRequest) {
        _topicOfferRequest = [[AMTopicOfferRequest alloc]init];
    }
    _topicOfferRequest.pageIndex = [NSNumber numberWithInt:self.currentPageIndex];
    _topicOfferRequest.topicId = self.activityId;
    _topicOfferRequest.pageSize = [NSNumber numberWithInt:8];
    return _topicOfferRequest;
}

-(AMSpecialPriceOfferRequest *)specialPriceOfferRequest
{
    if(!_specialPriceOfferRequest){
        _specialPriceOfferRequest = [[AMSpecialPriceOfferRequest alloc]init];
    }
    _specialPriceOfferRequest.industryId = self.industryId;
    _specialPriceOfferRequest.pageIndex = [NSNumber numberWithInt:self.currentPageIndex];
    return _specialPriceOfferRequest;
}

- (void)viewDidLoad
{

    [super viewDidLoad];
    // Do any additional setup after loading the view from its nib.
    
    //    [self.navigationController setNavigationBarHidden:YES animated:NO];
    [self initTitleAndRightButton];
    [self objManInit];
    self.displayModel = 1;
    
    isAllowSwitch = YES;
    
    //判断不同业务类型
    if ([[self contentData ] count] <= 0) {
        self.currentPageIndex = 1;
        switch(self.businessType){
            case AM_ACTIVITY_PRICE_TYPE_PRICE : 
                [self loadObjectsFromRemoteSpecial];
                break;
            case AM_ACTIVITY_PRICE_TYPE_PRICE_SMART : 
                [self loadObjectsFromRemoteSpecial];
                break;
            case AM_ACTIVITY_PRICE_TYPE_ACTIVITY : 
                [self loadObjectsFromRemoteTopic];
                break;
            case AM_ACTIVITY_PRICE_TYPE_STOCK : 
                [self loadObjectsFromRemoteTopic];
                break;
            case AM_ACTIVITY_PRICE_TYPE_ACTIVITY_HOME :
                [self loadObjectsFromRemoteTopic];
                break;
        } 
                
    }
    
}

- (void) handleTimer: (NSTimer *) timer
{
    NSLog(@"isAllowSwitch is YES");
    isAllowSwitch = YES;
}
- (void) initTitleAndRightButton
{
    NSString *title = [NSString stringWithFormat:@"%@",self.activityTitle];
    [self setTitle:title];    
    if(!_switchBtn){
        
        self.switchBtn = [[UIButton alloc] init];
        [_switchBtn setImage:[UIImage imageNamed:@"activity_icon_01.png"] forState:UIControlStateNormal];
        _switchBtn.frame = CGRectMake(0, 0, 44, 30);
        [_switchBtn addTarget:self action:@selector(switchTableview) forControlEvents:UIControlEventTouchUpInside];
        [super setNavigationRightItem:_switchBtn]; 
    }
    
}

- (void) switchTableview
{
    if(isAllowSwitch){
        isAllowSwitch = NO;
        self.timer = [NSTimer scheduledTimerWithTimeInterval: 0.5
                                                      target: self
                                                    selector: @selector(handleTimer:)
                                                    userInfo: nil
                                                     repeats: NO];
        
        //    NSInteger nowSwitchTime = [[NSDate date] timeIntervalSince1970];
        //    if((nowSwitchTime - _lastSwitchTime)>=1){
        //        _lastSwitchTime = nowSwitchTime;
        //    }else{
        //        return;
        //    }
        switch(self.businessType){
            case AM_ACTIVITY_PRICE_TYPE_PRICE :
                [AMLogUtils appendLog: HOME_TODAY_PRICE_BUTTON];
                break;
            case AM_ACTIVITY_PRICE_TYPE_PRICE_SMART :
                [AMLogUtils appendLog: TODAY_PRICE_BUTTON];
                break;
            case AM_ACTIVITY_PRICE_TYPE_ACTIVITY :
                [AMLogUtils appendLog: TODAY_ACTITY_BUTTON];
                break;
            case AM_ACTIVITY_PRICE_TYPE_STOCK :
                [AMLogUtils appendLog: SMALL_COMMODITY_BUTTON];
                break;
            case AM_ACTIVITY_PRICE_TYPE_ACTIVITY_HOME :
                [AMLogUtils appendLog: HOME_TODAY_ACTITY_BUTTON];
                break;
        }
        
        
        NSLog(@"offerPosition=%@",[NSNumber numberWithInt:self.offerPosition]);
        
        //针对网络情况不好或无网络的情况下，点击切换按钮无效
        if(!self.isLoading&&!isOffLine){
            
            if(self.displayModel==0){
                [_switchBtn setImage:[UIImage imageNamed:@"activity_icon_01.png"] forState:UIControlStateNormal];
                NSArray *visibleCellsArray = [self.mTableView indexPathsForVisibleRows];
                NSIndexPath *currentPath = nil;
                if(visibleCellsArray){
                    if([visibleCellsArray count]>1){
                        currentPath = [visibleCellsArray objectAtIndex:1];
                    }else{
                        currentPath = [visibleCellsArray objectAtIndex:0];
                    }
                    self.offerPosition = [[NSNumber numberWithInt:currentPath.row] intValue];
                    NSLog(@"smallCurrentPathIndexPath=%@",[NSNumber numberWithInt:currentPath.row]);
                    
                    self.displayModel=1;
                    [self.mTableView reloadData ];
                    int num= self.offerPosition/[AMTodayActivityBlockBoxCell cellBoxViewArrayCount];
                    
                    if (self.offerPosition%[AMTodayActivityBlockBoxCell cellBoxViewArrayCount]) {
                        num++;
                    }
                    
                    NSIndexPath *idxPath = [NSIndexPath indexPathForRow:num-1 inSection:0];
                    [self.mTableView scrollToRowAtIndexPath:idxPath
                                           atScrollPosition:UITableViewScrollPositionMiddle
                                                   animated:NO];
                }
                
            }else if(self.displayModel==1){
                [_switchBtn setImage:[UIImage imageNamed:@"activity_icon_02.png"] forState:UIControlStateNormal];
                NSArray *visibleCellsArray = [self.mTableView indexPathsForVisibleRows];
                NSIndexPath *currentPath = nil;
                if(visibleCellsArray){
                    if([visibleCellsArray count]>1){
                        currentPath = [visibleCellsArray objectAtIndex:1];
                    }else{
                        currentPath = [visibleCellsArray objectAtIndex:0];
                    }
                    self.offerPosition = [[NSNumber numberWithInt:currentPath.row] intValue];
                    
                    self.displayModel=0;
                    [self.mTableView reloadData ];
                    int num= (self.offerPosition)*2;
                    NSIndexPath *idxPath = [NSIndexPath indexPathForRow:num inSection:0];
                    [self.mTableView scrollToRowAtIndexPath:idxPath
                                           atScrollPosition:UITableViewScrollPositionMiddle
                                                   animated:NO];
                }
            }
            
        }

    }
   
}



- (void)viewWillAppear:(BOOL)animated{
    //对于提示文案，根据运营同学要求，暂时关闭
//    if(self.businessType==AM_ACTIVITY_PRICE_TYPE_STOCK){
//        UIView *headerView = [[UIView alloc]initWithFrame:CGRectMake(0.0, 0.0, 320.0, 40.0)];
//        headerView.backgroundColor = RGB(0xff, 0xfd, 0xe9);
//        
//        CGSize labelSize = [@"15天销不出，包退换货，真正零风险！" sizeWithFont:[UIFont systemFontOfSize:14.0f]];
//        UILabel *preLabel = [[UILabel alloc] initWithFrame:CGRectMake(50, 10, labelSize.width, 20)];
//        preLabel.font = [UIFont systemFontOfSize:12.0f];
//        preLabel.numberOfLines = 1;
//        preLabel.lineBreakMode = UILineBreakModeWordWrap;
//        preLabel.backgroundColor = [UIColor clearColor];
//        preLabel.textColor = [UIColor redColor];
//        preLabel.highlightedTextColor = RGB(0x66,0x66,0x66);
//        preLabel.text = @"15天销不出，包退换货，真正零风险！";
//        
//        [headerView addSubview:preLabel];
//        [self.view addSubview:headerView];
//        self.mTableView.tableHeaderView=headerView;
//        [preLabel release];
//        [headerView release];
//        
//    }
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section{

    if(self.displayModel==0){
      return [self.contentData count];  
    }else{
        int num= [self.contentData count]/[AMTodayActivityBlockBoxCell cellBoxViewArrayCount];
        
        if ([self.contentData count]%[AMTodayActivityBlockBoxCell cellBoxViewArrayCount]) {
            num++;
        }
        return num;
    }
}



- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath{
    
    
    NSUInteger row = [indexPath row];

    if(self.displayModel==0){
//        self.offerPosition = row;
        AMActivityDetailCell *cell = (AMActivityDetailCell *)[tableView dequeueReusableCellWithIdentifier: [AMActivityDetailCell cellIdentifer]];
        
        if (cell == nil){
            cell = [AMActivityDetailCell createCell];  
        }
        
        AMSpecialPriceOffer *offer = [self.contentData objectAtIndex:row];
        cell.subjectLabel.text = offer.subject;
        [cell insertSubview:cell.subjectLabel aboveSubview:cell.backgroundImage];
        if(self.businessType==AM_ACTIVITY_PRICE_TYPE_PRICE||self.businessType==AM_ACTIVITY_PRICE_TYPE_PRICE_SMART){
            [self setLeaveFactoryAndUnitPropertyPrice:offer.specialPrice originalPrice:offer.originalPrice cell:cell];
        }else{
//            [self setLeaveFactoryAndUnitPropertyPrice:@"20.0" originalPrice:@"18.0" cell:cell];
            [self setLeaveFactoryAndUnitProperty:[NSString stringWithFormat:@"%2g元/",[offer.price.amount doubleValue]] unit:offer.unit cell:cell];
        }
        NSString *listImg = [NSString stringWithFormat:@"%@",offer.listImgUrl];
//        NSString *bigImage = [listImg stringByReplacingOccurrencesOfString:@".100x100x80x1.jpg" withString:@".310x310x80x1.jpg"];
        
        
        
        NSString *bigImage = [listImg stringByReplacingOccurrencesOfString:@".100x100x80x1.jpg" withString:@".440x440x80x1.jpg"];
        [cell.listImg clear];
        cell.listImg.url = [NSURL URLWithString:bigImage];
        [self.objMan manage:cell.listImg];
        cell.selectionStyle = UITableViewCellSelectionStyleNone;//设置cell不可点击
        return cell;
    }else{
            
        AMTodayActivityBlockBoxCell *cell = (AMTodayActivityBlockBoxCell *)[tableView dequeueReusableCellWithIdentifier: [AMTodayActivityBlockBoxCell cellIdentifer]];
        if (cell == nil)  
        {
            NSArray *nib = [[NSBundle mainBundle] loadNibNamed:@"AMTodayActivityBlockBoxCell" 
                                                         owner:self options:nil];
            for (id oneObject in nib)
                if ([oneObject isKindOfClass:[AMTodayActivityBlockBoxCell class]])
                    cell = (AMTodayActivityBlockBoxCell *)oneObject;
        }
        
        
        NSUInteger index = [indexPath row] *[AMTodayActivityBlockBoxCell cellBoxViewArrayCount];
        
        for (AMTodayActivityBoxView *box in cell.cellBoxViewArray) {
            box.hidden = NO;
            if (index>=[self.contentData count]) {
                box.hidden = YES;//避免由于count为奇数造成的另外一个box view被复用显示的bug
                break;
            }
            box.tag = index;
            AMSpecialPriceOffer *offer = [self.contentData objectAtIndex:index++];
            box.subject.text = offer.subject;
            box.subject.textAlignment = UITextAlignmentLeft;
            NSString *listImg = [NSString stringWithFormat:@"%@",offer.listImgUrl];
            NSString *bigImage = [listImg stringByReplacingOccurrencesOfString:@".100x100x80x1.jpg" withString:@".220x220x80x1.jpg"];
#warning 修改人 孟希羲
            [box.listImg clear];//避免图片复用
            box.listImg.url = [NSURL URLWithString:bigImage];
            box.listImg.frame = CGRectMake(4, 4, 147, 145);
            box.listImg.layer.masksToBounds = YES;
            box.listImg.layer.cornerRadius= 10.0;
            [self.objMan manage:box.listImg];
            if(self.businessType==AM_ACTIVITY_PRICE_TYPE_PRICE||self.businessType==AM_ACTIVITY_PRICE_TYPE_PRICE_SMART){
                [self setLeaveFactoryAndUnitPropertyPriceBox:offer.specialPrice originalPrice:offer.originalPrice box:box];
            }else{
                [self setLeaveFactoryAndUnitPropertyBox:[NSString stringWithFormat:@"%2g元/",[offer.price.amount doubleValue]] unit:offer.unit box:box];
//                [self setLeaveFactoryAndUnitPropertyPriceBox:@"20.0" originalPrice:@"18.0" box:box];
            }
            
            [box addTarget:self action:@selector(boxUpAction:)  forControlEvents:UIControlEventTouchUpInside];    
        }
//        NSLog(@"tableview cell position=%@",[NSNumber numberWithInt:self.offerPosition]);
        cell.selectionStyle = UITableViewCellSelectionStyleNone;//设置cell不可点击
        return cell;
    }
    
}



- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath{
    if(self.displayModel==0){
      return [AMActivityDetailCell cellHeight];  
    }else{
        return [AMTodayActivityBlockBoxCell cellHeight];
    }
}


- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath{
    
    
    if(self.displayModel==0){
        
        switch(self.businessType){
            case AM_ACTIVITY_PRICE_TYPE_PRICE : 
                [AMLogUtils appendLog: HOME_TODAY_PRICE_OFFER_ITEM];
                break;
            case AM_ACTIVITY_PRICE_TYPE_PRICE_SMART : 
                [AMLogUtils appendLog: TODAY_PRICE_OFFER_ITEM];
                break;
            case AM_ACTIVITY_PRICE_TYPE_ACTIVITY : 
                [AMLogUtils appendLog: TODAY_ACTITY_OFFER_ITEM];
                break;
            case AM_ACTIVITY_PRICE_TYPE_STOCK : 
                [AMLogUtils appendLog: SMALL_COMMODITY_OFFER_ITEM];
                break;
            case AM_ACTIVITY_PRICE_TYPE_ACTIVITY_HOME :
                [AMLogUtils appendLog: HOME_TODAY_ACTITY_OFFER_ITEM];
                break;
        } 
        
        NSUInteger row = [indexPath row];
        AMSpecialPriceOffer *offer = (AMSpecialPriceOffer*)[self.contentData objectAtIndex:row] ;
        NSString *offerIdString = [NSString stringWithFormat:@"%@",offer.offerId];
        AMOfferTabViewController * controller = [[AMOfferTabViewController alloc] initWithOfferId:offerIdString offerName:offer.subject preViewName:nil];  
        controller.hidesBottomBarWhenPushed=YES;
        [self.navigationController pushViewController:controller animated:YES]; 
        [controller release];
        [tableView deselectRowAtIndexPath:indexPath animated:NO];

    }
    
}

-(void)boxDownAction:(AMTodayActivityBoxView*)sender
{
    sender.leaveFactoryImageFocusIcon.frame = CGRectMake(0,10, 130,190);
    sender.leaveFactoryImageFocusIcon.image = [UIImage imageNamed:@"App_icon_press"]; 
    
}
-(void)boxUpAction:(AMTodayActivityBoxView*)sender
{
    switch(self.businessType){
        case AM_ACTIVITY_PRICE_TYPE_PRICE : 
            [AMLogUtils appendLog: HOME_TODAY_PRICE_OFFER_ITEM];
            break;
        case AM_ACTIVITY_PRICE_TYPE_PRICE_SMART : 
            [AMLogUtils appendLog: TODAY_PRICE_OFFER_ITEM];
            break;
        case AM_ACTIVITY_PRICE_TYPE_ACTIVITY : 
            [AMLogUtils appendLog: TODAY_ACTITY_OFFER_ITEM];
            break;
        case AM_ACTIVITY_PRICE_TYPE_STOCK : 
            [AMLogUtils appendLog: SMALL_COMMODITY_OFFER_ITEM];
            break;
        case AM_ACTIVITY_PRICE_TYPE_ACTIVITY_HOME :
            [AMLogUtils appendLog: HOME_TODAY_ACTITY_OFFER_ITEM];
            break;
    } 
    
    AMSpecialPriceOffer *offer = [self.contentData objectAtIndex:sender.tag]; 
    NSString *offerIdString = [NSString stringWithFormat:@"%@",offer.offerId];
    AMOfferTabViewController * controller = [[AMOfferTabViewController alloc] initWithOfferId:offerIdString offerName:offer.subject preViewName:nil];  
    controller.hidesBottomBarWhenPushed=YES;
    [self.navigationController pushViewController:controller animated:YES]; 
    [controller release];
    
}

-(void)boxUpOutsideAction:(AMTodayActivityBoxView*)sender
{
    sender.leaveFactoryImageFocusIcon.image = nil; 
}

- (void) setLeaveFactoryAndUnitProperty:(NSString *)countValue unit:(NSString *)unitValue cell:(AMActivityDetailCell *) cellValue{
    
    
    CGSize labelSize = [countValue sizeWithFont:[UIFont systemFontOfSize:14.0f]];
    cellValue.leaveFactoryPriceAmountLabel.frame = CGRectMake(64, 330, labelSize.width, 36);
    cellValue.leaveFactoryPriceAmountLabel.text = countValue;
    
    CGSize labelSizeEnd = [unitValue sizeWithFont:[UIFont systemFontOfSize:14.0f]];
    
    cellValue.unitLabel.frame = CGRectMake(64+labelSize.width, 339, labelSizeEnd.width, labelSizeEnd.height);
    cellValue.unitLabel.text = unitValue;
    
    [cellValue insertSubview:cellValue.leaveFactoryPriceAmountPreLabel aboveSubview:cellValue.backgroundImage];
    [cellValue insertSubview:cellValue.leaveFactoryPriceAmountLabel aboveSubview:cellValue.backgroundImage];
    [cellValue insertSubview:cellValue.unitLabel aboveSubview:cellValue.backgroundImage];
    
    
}

- (void) setLeaveFactoryAndUnitPropertyPrice:(NSString *)specialPrice originalPrice:(NSString *)originalPrice cell:(AMActivityDetailCell *) cellValue{
    [cellValue.leaveFactoryPriceAmountPreLabel removeFromSuperview];
    CGSize labelSize = [specialPrice sizeWithFont:[UIFont systemFontOfSize:14.0f]];
    cellValue.leaveFactoryPriceAmountLabel.frame = CGRectMake(65, 330, labelSize.width+100, 36);
    cellValue.leaveFactoryPriceAmountLabel.text = [NSString stringWithFormat:@"¥%@",specialPrice];
    
    CGSize labelSizeEnd = [originalPrice sizeWithFont:[UIFont systemFontOfSize:14.0f]];
    
    cellValue.unitLabel.frame = CGRectMake(10+labelSize.width+180, 339, labelSizeEnd.width+100, labelSizeEnd.height);
    cellValue.unitLabel.text = [NSString stringWithFormat:@"¥%@",originalPrice];
    
    [cellValue insertSubview:cellValue.leaveFactoryPriceAmountPreLabel aboveSubview:cellValue.backgroundImage];
    [cellValue insertSubview:cellValue.leaveFactoryPriceAmountLabel aboveSubview:cellValue.backgroundImage];
    
    [cellValue insertSubview:cellValue.unitLabel aboveSubview:cellValue.backgroundImage];
    
    for (UIView*view in cellValue.subviews )  {
        if ([view isKindOfClass:[UIImageView class]]&&view.tag==521) {
            [view removeFromSuperview];
        }
    }
    
    UIImageView  *line = [[UIImageView alloc] initWithFrame:CGRectMake(10+labelSize.width+180, 339+labelSizeEnd.height/2, labelSizeEnd.width+5, 1)];
    line.image = [UIImage imageNamed:@"sep_line.png"];
    line.tag = 521;
    [cellValue addSubview:line];
    [line release];
    
    
}

- (void) setLeaveFactoryAndUnitPropertyPriceBox:(NSString *)specialPrice originalPrice:(NSString *)originalPrice box:(AMTodayActivityBoxView *) boxValue{
    
    [boxValue.leaveFactoryPricePre removeFromSuperview];
    CGSize labelSize = [specialPrice sizeWithFont:[UIFont systemFontOfSize:12.0f]];
    boxValue.leaveFactoryPrice.text = [NSString stringWithFormat:@"¥%@",specialPrice];
    boxValue.leaveFactoryPrice.frame = CGRectMake(10, 173, labelSize.width+10, labelSize.height);
    CGSize labelSizeEnd = [originalPrice sizeWithFont:[UIFont systemFontOfSize:12.0f]];
    
    boxValue.unit.frame = CGRectMake(10+labelSize.width+50, 173, labelSizeEnd.width+10, labelSizeEnd.height);
    boxValue.unit.text = [NSString stringWithFormat:@"¥%@",originalPrice];
    
    for (UIView*view in boxValue.subviews )  {
        if ([view isKindOfClass:[UIImageView class]]&&view.tag==520) {
            [view removeFromSuperview];
        }
    }
    
    UIImageView  *line = [[UIImageView alloc] initWithFrame:CGRectMake(10+labelSize.width+50, 173+labelSizeEnd.height/2, labelSizeEnd.width+5, 1)];
    line.image = [UIImage imageNamed:@"sep_line.png"];
    line.tag = 520;
    [boxValue addSubview:line];
    [line release];
    
}


- (void) setLeaveFactoryAndUnitPropertyBox:(NSString *)countValue unit:(NSString *)unitValue box:(AMTodayActivityBoxView *) boxValue{
    
    
//    NSString *leaveFactoryPricePreString = @"出厂价:";
//    CGSize labelSizeLeaveFactory = [leaveFactoryPricePreString sizeWithFont:[UIFont systemFontOfSize:12.0f]];
    
    CGSize labelSize = [countValue sizeWithFont:[UIFont systemFontOfSize:12.0f]];
    boxValue.leaveFactoryPrice.text = [NSString stringWithFormat:@"%@",countValue];

    CGSize labelSizeEnd = [unitValue sizeWithFont:[UIFont systemFontOfSize:12.0f]];
    
//    boxValue.unit.frame = CGRectMake(50+labelSize.width, 158, 147-labelSize.width-labelSizeEnd.width-labelSizeLeaveFactory.width, labelSizeEnd.height);
    boxValue.unit.frame = CGRectMake(50+labelSize.width, 173, labelSizeEnd.width, labelSizeEnd.height);
    boxValue.unit.text = unitValue;
}


- (void)loadObjectsFromRemoteSpecial {
    
    self.isLoading = YES;
    if (self.currentPageIndex>1) {
        AMMoreLoadingView * moreloadingView = [[AMMoreLoadingView alloc] init];
        self.mTableView.tableFooterView = moreloadingView;
        [moreloadingView release];
    }else {
        [self.mLoadingView showLoadingView];
    }
    
    
//    
//    self.isLoading = YES;
//    [self showLoadingView];
    // Load the object model via RestKit	
    RKObjectManager* objectManager = [RKObjectManager sharedManager];
    objectManager.client.baseURL = [RKURL URLWithString:AMCONST_BASE_URL];
//    objectManager.client.baseURL = [RKURL URLWithString:@"http://172.22.35.80/openapi/json2/1/ali.mobile"];
    
//    // Register our mappings with the provider
//    RKObjectMapping* mapping = [AMSpecialPriceOfferResult sharedObjectMapping];
//    [objectManager.mappingProvider addObjectMapping: mapping];
    
    [objectManager loadObjectsAtResourcePath:OCEAN_API_URL_SPECIAL_PRICE_OFFER_LIST usingBlock:^(RKObjectLoader* loader) {
        // Backend returns objects as a naked array in JSON, so we instruct the loader
        // to user the appropriate object mapping
        loader.delegate = self;
        if ([objectManager.acceptMIMEType isEqualToString:RKMIMETypeJSON]) {
//            loader.objectMapping = [objectManager.mappingProvider objectMappingForClass:[AMSpecialPriceOfferResult  class]];
            loader.objectMapping = [AMSpecialPriceOfferResult sharedObjectMapping];
        }
        
        // Change Method to POST
        loader.method = RKRequestMethodPOST;
        loader.params = self.specialPriceOfferRequest;
    }];
    //[super loadObjectsFromRemote];
    
}

- (void)loadObjectsFromRemoteTopic {
    
    
    self.isLoading = YES;
    if (self.currentPageIndex>1) {
        AMMoreLoadingView * moreloadingView = [[AMMoreLoadingView alloc] init];
        self.mTableView.tableFooterView = moreloadingView;
        [moreloadingView release];
    }
    else {
        [self.mLoadingView showLoadingView];
    }
    
    
//    self.isLoading = YES;
//    [self showLoadingView];
    // Load the object model via RestKit	
    RKObjectManager* objectManager = [RKObjectManager sharedManager];
    objectManager.client.baseURL = [RKURL URLWithString:AMCONST_BASE_URL];
    
    // Register our mappings with the provider
    RKObjectMapping* mapping = [AMSpecialPriceOfferResult sharedObjectMapping];
    [objectManager.mappingProvider addObjectMapping: mapping];
    
    [objectManager loadObjectsAtResourcePath:OCEAN_API_URL_TOPIC_OFFER_LIST usingBlock:^(RKObjectLoader* loader) {
        // Backend returns objects as a naked array in JSON, so we instruct the loader
        // to user the appropriate object mapping
        loader.delegate = self;
        if ([objectManager.acceptMIMEType isEqualToString:RKMIMETypeJSON]) {
            loader.objectMapping = [objectManager.mappingProvider objectMappingForClass:[AMSpecialPriceOfferResult  class]];
        }
        
        // Change Method to POST
        loader.method = RKRequestMethodPOST;
        loader.params = self.topicOfferRequest;
    }];
    //    [super loadObjectsFromRemote];
    
}

- (void)request:(RKRequest*)request didLoadResponse:(RKResponse*)response {
    NSLog(@"Loaded payload: %@", [response bodyAsString]);
}

extern NSInteger gLastDisplayErrorTimeInterval;
- (void)request:(RKRequest*)request didFailLoadWithError:(NSError *)error {
    NSLog(@"RKRequset didFailLoadWithError: %@", error);
    
    NSInteger currentTime = [[NSDate date] timeIntervalSince1970];
    if ( [error code] == RKRequestBaseURLOfflineError && currentTime - gLastDisplayErrorTimeInterval > 3 ) {
//        NSString *errorMsg = NSLocalizedString(@"Failed to connect with server", nil);
//        [UIHelp showAlertDialogWithTitle:nil andMsg:errorMsg];
        
        gLastDisplayErrorTimeInterval = currentTime;
    }else if ([error code] == RKRequestConnectionTimeoutError  && currentTime - gLastDisplayErrorTimeInterval > 3 ) {
//        NSString *errorMsg = NSLocalizedString(@"Connect to server timeout", nil);
//        [UIHelp showAlertDialogWithTitle:nil andMsg:errorMsg];    
        
        gLastDisplayErrorTimeInterval = currentTime;
    }
}

- (void)objectLoader:(RKObjectLoader *)objectLoader didFailWithError:(NSError *)error{
    [self.mLoadingView endLoadingView];
    isOffLine = YES;
    //NSURLErrorDomain Code=-1009 "The Internet connection appears to be offline
    if ([error code] == RKRequestBaseURLOfflineError||[error code] ==RKRequestConnectionTimeoutError||[error code] ==-1009){
        if ([self.contentData count]) {
            AMErrorMessageView * errorMessageView = [[AMErrorMessageView alloc] init];
            self.mTableView.tableFooterView = errorMessageView;
            [errorMessageView release];
            self.currentPageIndex--;
        }else {
            [self.mLoadingView showLoadFailedMessageForRequest:objectLoader];
        }
        
    }
    self.isLoading = NO;
}

- (void)objectLoader:(RKObjectLoader*)objectLoader didLoadObjects:(NSMutableArray*)objects {
    
    isOffLine = NO;
    self.isLoading = NO;
    
    if([objectLoader.params isKindOfClass:[AMTopicOfferRequest class]]){
        if (self.currentPageIndex*[self.topicOfferRequest.pageSize intValue] >= self.totalCount) {
            self.mTableView.tableFooterView = nil;
        }
    }else if([objectLoader.params isKindOfClass:[AMSpecialPriceOfferRequest class]]){
        if (self.currentPageIndex*[self.specialPriceOfferRequest.pageSize intValue] >= self.totalCount) {
            self.mTableView.tableFooterView = nil;
        }
    }

        
    
    
//    self.isLoading = NO;
    id object = [objects objectAtIndex:0];
    [self endLoadingView];
    
    if(object!=nil){
        AMSpecialPriceOfferResult * offer = object;
        NSArray * array = offer.resultList;
        self.totalCount = [offer.totalCount intValue];
//        [self.contentData removeAllObjects];
        [self.contentData addObjectsFromArray:array];
        [self.mTableView reloadData];

    }
    
    isLoading = NO;
}

- (void) setTableDate:(NSMutableArray *)date
{
    
    [self.contentData addObjectsFromArray:date];
    [self.mTableView reloadData];
}


- (void)scrollViewDidScroll: (UIScrollView*)scroll {
    // UITableView only moves in one direction, y axis
    NSInteger currentOffset = scroll.contentOffset.y;
    NSInteger maximumOffset = scroll.contentSize.height - scroll.frame.size.height;
    
    // Change 10.0 to adjust the distance from bottom
    if (maximumOffset - currentOffset <= 30.0) {
        if(self.businessType==AM_ACTIVITY_PRICE_TYPE_PRICE||self.businessType==AM_ACTIVITY_PRICE_TYPE_PRICE_SMART){
//            if ([self.contentData count]<self.totalCount)
            if (self.currentPageIndex*[self.topicOfferRequest.pageSize intValue] < self.totalCount) 

            {
                if (!self.isLoading) {
                    self.currentPageIndex++;
                    [self loadObjectsFromRemoteSpecial];   
                }
            }  
        }else {
//            if ([self.contentData count]<self.totalCount)
            if (self.currentPageIndex*[self.topicOfferRequest.pageSize intValue] < self.totalCount)
            {
                if (!self.isLoading) {
                    self.currentPageIndex++;
                    [self loadObjectsFromRemoteTopic];   
                }
            }  

        }    
        
    }
}

@end
