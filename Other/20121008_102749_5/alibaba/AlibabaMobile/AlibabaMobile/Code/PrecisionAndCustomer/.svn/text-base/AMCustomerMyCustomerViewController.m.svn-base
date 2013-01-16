
//  AMFavoritesViewController.m
//
//  Created by zzh on 11-12-21.
//  Copyright (c) 2011å¹´ __MyCompanyName__. All rights reserved.
//

#import <QuartzCore/QuartzCore.h>
#import "AMCustomerMyCustomerViewController.h"
#import "AMOfferTabViewController.h"
#import "AMCompanyTabViewController.h"
#import "AMIMViewController.h"
#import "LoginToken.h"
#import "AliTabViewController.h"
#import "AliNavigationBackButton.h"
#import "AliNavigationTitleLabel.h"
#import "AliImageControlFactory.h"
#import "UIHelp.h"
#import "AMMoreLoadingCell.h"
#import "AliTableViewCellAllVisitor.h"
#import "AMCustomerSuggestListMainModel.h"
#import "AliTableViewCellCompanyDetail.h"
#import "AliTableViewCellPriceDetail.h"
#import "NSAttributedString+HTML.h"
#import "ConstDef.h"
#import "AMCUDResult.h"
#import "AMCustomerSuggestListResult.h"
#import "AMFavoriteCompany.h"
#import "AMCompanyFavoriteListResult.h"
#import "AMFavoriteOffer.h"
#import "AMPriceResult.h"
#import "AMMoney.h"
#import "AliToastView.h"
#import "AMLogTypeCode.h"
#import "AMLogUtils.h"
#import "NSAttributedString+HTML.h"
#import "AMRequestDelegate.h"
#import "AliTableViewCellSuggest.h"
#import "AMCustomerSuggestStatRequest.h"
#import "AMCustomerSuggestStatResult.h"
#import "AMCustomerMyCustomerRequest.h"
#import "AMCustomerMyCustomerGroupRequest.h"
#import "AMCustomerMyCustomerResult.h"
#import "AMCustomerMyCustomerGroupListResult.h"
#import "AMCustomerMyCustomerGroupResult.h"
#import "AMCustomerMyCustomerListModel.h"
#import "AMCustomerInfoViewController.h"
#import "AliTableViewCellMyCustomer.h"
#import "NoticationItem.h"
#import "AMCustomerMyCustomerGroupModel.h"
#import "AMIMTalkViewController.h"
#import "AMMoreLoadingView.h"
#import "AMErrorMessageView.h"

#define RGB(r, g, b) [UIColor colorWithRed:r/255.0 green:g/255.0 blue:b/255.0 alpha:1.0]
#define DEFAULT_PAGE_SIZE  9
#define DEFAULT_FONT_SIZE  12.0f
#define BUTTON_ALL_CATEGORY  0
#define BUTTON_ALL_AREA  1
#define BUTTON_QUICK_SEARCH  2
@interface AMCustomerMyCustomerViewController()
@property (nonatomic,copy)NSString *loginUserName;
@property (nonatomic,assign) NSInteger tempCurrentPage;
@end

@implementation AMCustomerMyCustomerViewController

@synthesize myCustomerTableView;
@synthesize myCustomersObjects = _myCustomersObjects;
@synthesize myCustomersGroupObjects = _myCustomersGroupObjects;
@synthesize myCustomersAreaObjects = _myCustomersAreaObjects;
@synthesize myCustomerRequest = _myCustomerRequest;
@synthesize myCustomerGroupRequest = _myCustomerGroupRequest;
@synthesize objMan;
@synthesize mLoadingView = _mLoadingView;
@synthesize loginUserName=_loginUserName;
@synthesize mNavigationController = _mNavigationController;
@synthesize headerView = _headerView;

@synthesize categoryPicker=_categoryPicker;
@synthesize areaPicker = _areaPicker;
@synthesize buttonAllCategory = _buttonAllCategory;
@synthesize buttonAllArea = _buttonAllArea;
@synthesize buttonQuickSearch = _buttonQuickSearch;

@synthesize searchView=_searchView;
@synthesize cancelButton = _cancelButton;
@synthesize mMyCustomerSelectionView = _mMyCustomerSelectionView;
@synthesize allAreaDict = _allAreaDict;
@synthesize allCategoryDict = _allCategoryDict;
@synthesize totalCount = _totalCount;
@synthesize totalCountLabel = _totalCountLabel;
@synthesize totalPreLabel = _totalPreLabel;
@synthesize totalMidLabel = _totalMidLabel;
@synthesize totalEndLabel = _totalEndLabel;
@synthesize isFirstLoadView = _isFirstLoadView;
@synthesize tempCurrentPage = _tempCurrentPage;
-(BOOL)disablesAutomaticKeyboardDismissal  
{  
    return YES;  
}

- (IBAction)cancelbtnClicked:(id)sender{
    _headerView.hidden = NO;
    _searchView.hidden = YES;
    
    //点击快速搜索需隐藏分组和地区以及去掉遮罩
    self.categoryPicker.hidden = YES;
    self.areaPicker.hidden = YES;
    if(self.mMyCustomerSelectionView){
        [self.mMyCustomerSelectionView removeFromSuperview];
    }
    
    //隐藏键盘
    [self.searchView keyDisappearForce];
}
-(void)searchBarEditViewEditBegin:(AliCustomerSearchView*)searchBarView
{
    
}

-(void)searchBarEditViewDidEnd:(AliCustomerSearchView *)searchView content:(NSString *)content selected:(NSUInteger)selected pickerContent:(NSString *)pickerContent
{
    [AMLogUtils appendLog:CUSTOMERMANAGER_MYCUSTOMER_FOUR];
    if(self.mMyCustomerSelectionView){
        [self.mMyCustomerSelectionView removeFromSuperview];
    }
    if(self.searchView.mMyCustomerSelectionView){
        [self.searchView.mMyCustomerSelectionView removeFromSuperview];
    }
    self.mLoadingView.noDataView.hidden = YES;
    isNeedReload = YES;
    if(pickerContent==nil){
        pickerContent=@"公司";
    }
    NSLog(@"searchBarEditViewDidEnd content = %@ pickerContent=%@",content,pickerContent);
    
    if([pickerContent isEqualToString:@"公司"]){
        [AMLogUtils appendLog:CUSTOMERMANAGER_MYCUSTOMER_FIVE];
        self.myCustomerRequest.corpName = content;
        self.myCustomerRequest.buyerName = nil;
        self.myCustomerRequest.phoneNumber = nil;
    }else if([pickerContent isEqualToString:@"联系人"]){
        [AMLogUtils appendLog:CUSTOMERMANAGER_MYCUSTOMER_SIX];
        self.myCustomerRequest.buyerName = content;
        self.myCustomerRequest.corpName = nil;
        self.myCustomerRequest.phoneNumber = nil;
    }else if([pickerContent isEqualToString:@"电话"]){
        [AMLogUtils appendLog:CUSTOMERMANAGER_MYCUSTOMER_SEVEN];
        self.myCustomerRequest.phoneNumber = content;
        self.myCustomerRequest.buyerName = nil;
        self.myCustomerRequest.corpName = nil;
    }
    [self loadRequest];
}
-(void)searchBarEditCancel:(AliCustomerSearchView*)searchBarView
{
    [AMLogUtils appendLog:CUSTOMERMANAGER_MYCUSTOMER_ELEVE];
    _searchView.hidden = YES;
    _headerView.hidden = NO;
}


-(void)pickerView:(AliTableViewMyCustomerPickerView*)picker selected:(NSUInteger)selectedPicker content:(NSString *)content type:(NSUInteger)type{
    NSLog(@"selectedPicker=%d,type=%d",selectedPicker,type);
    
    isNeedReload = YES;
    currentMyCustomerPage = 1;
    
    self.myCustomerRequest.corpName = nil;
    self.myCustomerRequest.buyerName = nil;
    self.myCustomerRequest.phoneNumber = nil;
    
    switch (type) {
        case 0:
        {

            if([content canBeConvertedToEncoding:NSASCIIStringEncoding]){
                if(content.length>8){
                    content = [NSString stringWithFormat:@"%@...",[content substringWithRange:NSMakeRange(0,7)]];
                }
            }else{
                if(content.length>4){
                    content = [NSString stringWithFormat:@"%@...",[content substringWithRange:NSMakeRange(0,3)]];
                }
            }
            
            [_buttonAllCategory setTitle:content forState:UIControlStateNormal];
            self.categoryPicker.hidden = YES;
            self.myCustomerRequest.groupId = [self.allCategoryDict objectForKey:content];
            [self loadRequest];
        }
            break;
        case 1:
        {
            if([content canBeConvertedToEncoding:NSASCIIStringEncoding]){
                if(content.length>8){
                    content = [NSString stringWithFormat:@"%@...",[content substringWithRange:NSMakeRange(0,7)]];
                }
            }else{
                if(content.length>4){
                    content = [NSString stringWithFormat:@"%@...",[content substringWithRange:NSMakeRange(0,3)]];
                }
            }
            
            [_buttonAllArea setTitle:content forState:UIControlStateNormal];
            self.areaPicker.hidden = YES;
            self.myCustomerRequest.province = [self.allAreaDict objectForKey:content];
            [self loadRequest];
        }    
        default:
            break;
    }
    [self.mMyCustomerSelectionView removeFromSuperview];
    isFromPicker = YES;
    
}

-(AliTableViewMyCustomerPickerView*)categoryPicker
{
    if (!_categoryPicker) {
        
        //        _categoryPicker = [[AliTableViewMyCustomerPickerView alloc] initWithGroupArray:[[NSMutableArray alloc] initWithObjects: @"所有分组",@"未分组",@"我的客户",@"浙江省",@"江西省",@"我的供应商",nil]];
        if(self.allCategoryDict==nil){
            self.allCategoryDict = [[NSMutableDictionary alloc] init];
        }
        NSMutableArray *groupArray = [[NSMutableArray alloc]init];
        for(int i=0;i<[self.myCustomersGroupObjects count];i++){
            AMCustomerMyCustomerGroupModel *result = [self.myCustomersGroupObjects objectAtIndex:i];
            [groupArray addObject:result.value ];
            [self.allCategoryDict setObject:result.identifier forKey:result.value];
        }
        _categoryPicker = [[AliTableViewMyCustomerPickerView alloc] initWithGroupArray:groupArray];
        [groupArray release];
        [_categoryPicker reloadData];
        _categoryPicker.hidden = YES;
        if (_categoryPicker.frame.size.height > 150) {
            _categoryPicker.frame = CGRectMake(68, 80, _categoryPicker.frame.size.width, 150);
        }else{
            _categoryPicker.frame = CGRectMake(68, 80, _categoryPicker.frame.size.width, _categoryPicker.frame.size.height);
        }
        _categoryPicker.delegatePicker = self;
        _categoryPicker.buttonPressType = BUTTON_ALL_CATEGORY;
    }
    
    return _categoryPicker;
}

-(AliTableViewMyCustomerPickerView*)areaPicker
{
    if (!_areaPicker) {
        if(self.allAreaDict==nil){
            self.allAreaDict = [[NSMutableDictionary alloc] init];
        }
        NSMutableArray *areaArray = [[NSMutableArray alloc]init];
        for(int i=0;i<[self.myCustomersAreaObjects count];i++){
            AMCustomerMyCustomerGroupModel *result = [self.myCustomersAreaObjects objectAtIndex:i];
            [areaArray addObject:result.value ];
            [self.allAreaDict setObject:result.identifier forKey:result.value];
        }
        _areaPicker = [[AliTableViewMyCustomerPickerView alloc] initWithGroupArray:areaArray];
        [areaArray release];
//        _areaPicker = [[AliTableViewMyCustomerPickerView alloc] initWithGroupArray:[[NSMutableArray alloc] initWithObjects: @"所有地区",@"杭州",@"北京",@"长沙",@"上海",@"广州",nil]];
        [_areaPicker reloadData];
//        [self.view addSubview:_areaPicker];
        _areaPicker.hidden = YES;
        if(_areaPicker.frame.size.height > 150){
            _areaPicker.frame = CGRectMake(148, 80, _areaPicker.frame.size.width, 150);
        }else{
            _areaPicker.frame = CGRectMake(148, 80, _areaPicker.frame.size.width, _areaPicker.frame.size.height);
        }
        _areaPicker.delegatePicker = self;
        _areaPicker.buttonPressType = BUTTON_ALL_AREA;
    }
    
    return _areaPicker;
}

-(UIView*)headerView
{
    if (!_headerView) {
        _headerView = [[UIView alloc]initWithFrame:CGRectMake(0.0, 40.0, 320.0, 40.0)];
        _headerView.backgroundColor = RGB(0xF2, 0xF2, 0xF2);
        
//        self.totalCountLabel = [[UILabel alloc]initWithFrame:CGRectMake(10.0, 10.0, 100, 20.0)];
//        _totalCountLabel.backgroundColor = [UIColor clearColor];
//        _totalCountLabel.textColor = RGB(0x66,0x66,0x66);
//        _totalCountLabel.highlightedTextColor = RGB(0x66,0x66,0x66);
//        _totalCountLabel.font = [UIFont fontWithName:@"Helvetica-Bold" size:14.f];
//        _totalCountLabel.textAlignment = UITextAlignmentLeft;
//        [_headerView addSubview:_totalCountLabel];
        
        
        self.buttonAllCategory = [[UIButton alloc]initWithFrame:CGRectMake(84.0, 5.0, 73.0, 30.0)];
        [_buttonAllCategory setTitle:@"全部分组" forState:UIControlStateNormal];
        [_buttonAllCategory setTitleEdgeInsets:UIEdgeInsetsMake(0, -10, 0, 0)];
        [_buttonAllCategory setBackgroundImage:[UIImage imageNamed:@"button_drop_n.png"] forState:UIControlStateNormal];
        [_buttonAllCategory setBackgroundImage:[UIImage imageNamed:@"button_drop_p_01.png"] forState:UIControlStateSelected];
        [_buttonAllCategory setBackgroundImage:[UIImage imageNamed:@"button_drop_p_01.png"] forState:UIControlStateHighlighted];
        
        

        [_buttonAllCategory.titleLabel setFont:[UIFont boldSystemFontOfSize:DEFAULT_FONT_SIZE]];
        [_buttonAllCategory setTitleColor:[UIColor blackColor] forState:UIControlStateNormal];
        _buttonAllCategory.tag = BUTTON_ALL_CATEGORY;
        [_buttonAllCategory addTarget:self action:@selector(changeState:) forControlEvents:UIControlEventTouchDown];
        [_headerView addSubview:_buttonAllCategory];

        self.buttonAllArea = [[UIButton alloc]initWithFrame:CGRectMake(168.0, 5.0, 70.0, 30.0)];
        [_buttonAllArea setTitle:@"所有地区" forState:UIControlStateNormal];
        [_buttonAllArea setTitleEdgeInsets:UIEdgeInsetsMake(0, -10, 0, 0)];
        [_buttonAllArea setBackgroundImage:[UIImage imageNamed:@"button_drop_n.png"] forState:UIControlStateNormal];
        [_buttonAllArea setBackgroundImage:[UIImage imageNamed:@"button_drop_p_01.png"] forState:UIControlStateSelected];
        [_buttonAllArea setBackgroundImage:[UIImage imageNamed:@"button_drop_p_01.png"] forState:UIControlStateHighlighted];
        [_buttonAllArea.titleLabel setFont:[UIFont boldSystemFontOfSize:DEFAULT_FONT_SIZE]];
        [_buttonAllArea setTitleColor:[UIColor blackColor] forState:UIControlStateNormal];
        _buttonAllArea.tag = BUTTON_ALL_AREA;
        [_buttonAllArea addTarget:self action:@selector(changeState:) forControlEvents:UIControlEventTouchDown];
        [_headerView addSubview:_buttonAllArea];
        
        self.buttonQuickSearch = [[UIButton alloc]initWithFrame:CGRectMake(250.0, 5.0, 60.0, 30.0)];
        [_buttonQuickSearch setTitle:@"快速搜索" forState:UIControlStateNormal];
        [_buttonQuickSearch setBackgroundImage:[UIImage imageNamed:@"app_button_nor.png"] forState:UIControlStateNormal];
        [_buttonQuickSearch setBackgroundImage:[UIImage imageNamed:@"app_button_p.png"] forState:UIControlStateSelected];
        [_buttonQuickSearch setBackgroundImage:[UIImage imageNamed:@"app_button_p.png"] forState:UIControlStateHighlighted];
        [_buttonQuickSearch.titleLabel setFont:[UIFont boldSystemFontOfSize:DEFAULT_FONT_SIZE]];
        [_buttonQuickSearch setTitleColor:[UIColor blackColor] forState:UIControlStateNormal];
        _buttonQuickSearch.tag = BUTTON_QUICK_SEARCH;
        [_buttonQuickSearch addTarget:self action:@selector(changeState:) forControlEvents:UIControlEventTouchDown];
        [_headerView addSubview:_buttonQuickSearch];
        
        
        
    }
    return _headerView;  
}


- (IBAction)changeState:(id)sender
{
    int index = ((UIButton *)sender).tag;
    switch (index) {
        case BUTTON_ALL_CATEGORY:
        {
            [AMLogUtils appendLog:CUSTOMERMANAGER_MYCUSTOMER_THREE];
            self.areaPicker.hidden = YES;//先隐藏区域
            NSLog(@"category button have clicked %d",index);
            
            if([self.myCustomersGroupObjects count]==1){
                AMCustomerMyCustomerGroupModel *model =  [self.myCustomersGroupObjects objectAtIndex:0];
                if([model.value isEqualToString:@"全部分组"]){
                    [[AliToastView MakeToastWithType:TOAST_STYLE_FAIL info:@"无分组信息！"] show];  
                }else{
                    if (self.categoryPicker.hidden) {
                        self.mMyCustomerSelectionView.frame = CGRectMake(0, 80, self.mMyCustomerSelectionView.frame.size.width, self.mMyCustomerSelectionView.frame.size.height);
                        [self.view insertSubview:self.mMyCustomerSelectionView belowSubview:self.categoryPicker];
                        self.categoryPicker.hidden = NO;
                    }
                    else {
                        [self.mMyCustomerSelectionView removeFromSuperview];
                        self.categoryPicker.hidden = YES;
                        
                    }
                    
                }
                
            }else{
                if (self.categoryPicker.hidden) {
                    self.mMyCustomerSelectionView.frame = CGRectMake(0, 80, self.mMyCustomerSelectionView.frame.size.width, self.mMyCustomerSelectionView.frame.size.height);
                    [self.view insertSubview:self.mMyCustomerSelectionView belowSubview:self.categoryPicker];
                    self.categoryPicker.hidden = NO;
                }
                else {
                    [self.mMyCustomerSelectionView removeFromSuperview];
                    self.categoryPicker.hidden = YES;
                    
                }
            }
            
        }
            break;
        case BUTTON_ALL_AREA:
        {
            [AMLogUtils appendLog:CUSTOMERMANAGER_MYCUSTOMER_TWO];
            self.categoryPicker.hidden = YES;//先隐藏分组
            NSLog(@"area button have clicked %d",index);
            if([self.myCustomersAreaObjects count]==0){
                NSLog(@"self.myCustomersAreaObjects count ==0");
                [[AliToastView MakeToastWithType:TOAST_STYLE_FAIL info:@"无地区信息！"] show];
            }else{
                if (self.areaPicker.hidden) {
                    self.mMyCustomerSelectionView.frame = CGRectMake(0, 80, self.mMyCustomerSelectionView.frame.size.width, self.mMyCustomerSelectionView.frame.size.height);
                    [self.view insertSubview:self.mMyCustomerSelectionView belowSubview:self.areaPicker];
                    self.areaPicker.hidden = NO;
                }
                else {
                    [self.mMyCustomerSelectionView removeFromSuperview];
                    self.areaPicker.hidden = YES;
                }    
            }
        }
            break;
        case BUTTON_QUICK_SEARCH:
        {
            [AMLogUtils appendLog:CUSTOMERMANAGER_MYCUSTOMER_ONE];
            NSLog(@"search button have clicked %d",index);
            _searchView.hidden= NO;
            _headerView.hidden = YES;
            _cancelButton.hidden = NO;
            
            //点击快速搜索需隐藏分组和地区以及去掉遮罩
            self.categoryPicker.hidden = YES;
            self.areaPicker.hidden = YES;
            if(self.mMyCustomerSelectionView){
                [self.mMyCustomerSelectionView removeFromSuperview];
            }
            
        }
            break;
        default:
            break;
    }
}

-(UIView*)mLoadingView
{
    if (!_mLoadingView) {
        
        NSArray *nib = [[NSBundle mainBundle] loadNibNamed:@"AliLoadingDataView" owner:self options:nil];
        for (id oneObject in nib)
            if ([oneObject isKindOfClass:[AliLoadingDataView class]])
                _mLoadingView = [(AliLoadingDataView *)oneObject retain];
        _mLoadingView.frame= CGRectMake(0,80,_mLoadingView.frame.size.width,_mLoadingView.frame.size.height);
        _mLoadingView.noDataView.backgroundColor =RGB(0xf0,0xf0,0xf0);
        _mLoadingView.noDataView.frame = CGRectMake(0,0,_mLoadingView.frame.size.width,_mLoadingView.frame.size.height);
        [self.view addSubview:_mLoadingView];
        [_mLoadingView setHidden:NO];
    }
    
    return _mLoadingView;
}


- (void) showLoadingView
{
    
    [self.mLoadingView showLoadingView];
    
}
//去除加载进度
-(void) endLoadingView
{
    [self.mLoadingView endLoadingView];
}
- (void) showNodataMessage
{
    [self.mLoadingView showNodataMessage];
//    [self.mLoadingView setHidden:NO];
//    [self.mLoadingView.loadingView setHidden:YES];
//    [self.mLoadingView.noDataView setHidden:NO];
}



- (id)initWithNavigation:(UINavigationController *)navigation
{
    self = [super init];
    if (self) {
        self.mNavigationController = navigation;
        self.isFirstLoadView = YES;
    }
    return self;
}

- (void)didReceiveMemoryWarning
{
//    [super didReceiveMemoryWarning];
    // Release any cached data, images, etc that aren't in use.
}


- (void)loadObjectsFromRemoteMyCustomer {
    
    if (currentMyCustomerPage>1) {
        AMMoreLoadingView * moreloadingView = [[AMMoreLoadingView alloc] init];
        self.myCustomerTableView.tableFooterView = moreloadingView;
        [moreloadingView release];
    }else {
        self.myCustomerTableView.tableFooterView = nil;
        [self.mLoadingView showLoadingView];
    }
    
    
//    if(isPullViewLoad){
//        isPullViewLoad = NO;
//    }else{
//        if(self.mLoadingView.loadingView.hidden==YES){
//            self.mLoadingView.loadingView.hidden = NO;
//        }
//        isLoading = YES;
//    }
//    
//    [self.mLoadingView.noDataView setHidden:YES];//去掉无结果显示的干扰
    isLoading = YES;
        
    // Load the object model via RestKit	
    RKObjectManager* objectManager = [RKObjectManager sharedManager];
    objectManager.client.baseURL = [RKURL URLWithString:AMCONST_BASE_URL];
    
    // Register our mappings with the provider
	RKObjectMapping* favResultMapping = [AMCustomerMyCustomerResult sharedObjectMapping];
    [objectManager.mappingProvider addObjectMapping: favResultMapping];
    
    [objectManager loadObjectsAtResourcePath:OCEAN_API_URL_CUSTOMER_MYCUSTOMER_LIST usingBlock:^(RKObjectLoader* loader) {
        // Backend returns objects as a naked array in JSON, so we instruct the loader
        // to user the appropriate object mapping
		loader.delegate = self.oceanClient;
        if ([objectManager.acceptMIMEType isEqualToString:RKMIMETypeJSON]) {
            loader.objectMapping = [objectManager.mappingProvider objectMappingForClass:[AMCustomerMyCustomerResult class]];
        }
        
        // Change Method to POST
        loader.method = RKRequestMethodPOST;
        loader.params = self.myCustomerRequest;
    }];
    
//    if(currentMyCustomerPage==1){
//        self.myCustomerTableView.tableFooterView = nil;
//    }
}

- (void)loadObjectsFromRemoteMyCustomerGroup {
//    isLoading = YES;
    // Load the object model via RestKit
    RKObjectManager* objectManager = [RKObjectManager sharedManager];
    objectManager.client.baseURL = [RKURL URLWithString:AMCONST_BASE_URL];
    
    // Register our mappings with the provider
	RKObjectMapping* groupResultMapping = [AMCustomerMyCustomerGroupResult sharedObjectMapping];
    [objectManager.mappingProvider addObjectMapping: groupResultMapping];
    
    [objectManager loadObjectsAtResourcePath:OCEAN_API_URL_CUSTOMER_MYCUSTOMER_GROUP_LIST usingBlock:^(RKObjectLoader* loader) {
        // Backend returns objects as a naked array in JSON, so we instruct the loader
        // to user the appropriate object mapping
		loader.delegate = self.oceanClient;
        if ([objectManager.acceptMIMEType isEqualToString:RKMIMETypeJSON]) {
            loader.objectMapping = [objectManager.mappingProvider objectMappingForClass:[AMCustomerMyCustomerGroupResult class]];
        }
        
        // Change Method to POST
        loader.method = RKRequestMethodPOST;
        loader.params = self.myCustomerGroupRequest;
    }];
}

#pragma mark RKObjectLoaderDelegate methods

- (void)request:(RKRequest*)request didLoadResponse:(RKResponse*)response {
    NSLog(@"Loaded payload: %@", [response bodyAsString]);
    
}

-(void)request:(RKRequest *)request didFailLoadWithError:(NSError *)error{
    [super request:request didFailLoadWithError:error];

}



- (void) setTotalCustomerProperty:(NSString *)countValue{
    
    if(self.totalPreLabel){
        [self.totalPreLabel removeFromSuperview];
    }
    if(self.totalMidLabel){
        [self.totalMidLabel removeFromSuperview];
    }
    if(self.totalEndLabel){
        [self.totalEndLabel removeFromSuperview];
    }
//    CGSize labelSizePre = [@"共" sizeWithFont:[UIFont fontWithName:@"Helvetica-Bold" size:14.0f]];
    CGSize labelSizePre = [@"共" sizeWithFont:[UIFont systemFontOfSize:14.0f]];
    self.totalPreLabel = [[UILabel alloc] initWithFrame:CGRectMake(10, 10, labelSizePre.width, 20)];
    _totalPreLabel.font = [UIFont systemFontOfSize:14.0f];
    _totalPreLabel.numberOfLines = 1;
    _totalPreLabel.lineBreakMode = UILineBreakModeWordWrap;
    _totalPreLabel.backgroundColor = [UIColor clearColor];
    _totalPreLabel.textColor = RGB(0x66,0x66,0x66);
    _totalPreLabel.highlightedTextColor = RGB(0x66,0x66,0x66);
    _totalPreLabel.font = [UIFont systemFontOfSize:14.0f];
    _totalPreLabel.text = @"共";
    [_headerView addSubview:_totalPreLabel];
    
    
    
    CGSize labelSize = [countValue sizeWithFont:[UIFont systemFontOfSize:14.0f]];
    self.totalMidLabel = [[UILabel alloc] initWithFrame:CGRectMake(10+_totalPreLabel.frame.size.width, 10, labelSize.width, 20)];
    _totalMidLabel.font = [UIFont systemFontOfSize:14.0f];
    _totalMidLabel.numberOfLines = 1;
    _totalMidLabel.lineBreakMode = UILineBreakModeWordWrap;
    _totalMidLabel.backgroundColor = [UIColor clearColor];
    _totalMidLabel.textColor = RGB(0xff,0x73,0x00);
    _totalMidLabel.highlightedTextColor = RGB(0xff,0x73,0x00);
    _totalMidLabel.font = [UIFont systemFontOfSize:14.0f];
    _totalMidLabel.text = countValue;
    [_headerView addSubview:_totalMidLabel];
    
    
    
    CGSize labelSizeEnd = [@"位" sizeWithFont:[UIFont systemFontOfSize:14.0f]];
    self.totalEndLabel = [[UILabel alloc] initWithFrame:CGRectMake(10+_totalPreLabel.frame.size.width+_totalMidLabel.frame.size.width, 10, labelSizeEnd.width, 20)];
    _totalEndLabel.font = [UIFont systemFontOfSize:14.0f];
    _totalEndLabel.numberOfLines = 1;
    _totalEndLabel.lineBreakMode = UILineBreakModeWordWrap;
    _totalEndLabel.backgroundColor = [UIColor clearColor];
    _totalEndLabel.textColor = RGB(0x66,0x66,0x66);
    _totalEndLabel.highlightedTextColor = RGB(0x66,0x66,0x66);
    _totalEndLabel.font = [UIFont systemFontOfSize:14.0f];
    _totalEndLabel.text = @"位";
    [_headerView addSubview:_totalEndLabel];
    
    
}


- (void)objectLoader:(RKObjectLoader*)objectLoader didLoadObjects:(NSMutableArray*)objects {
    
    NSLog(@"xxxxx Loaded objects: %@", objects);    
    if([objectLoader.params isKindOfClass:[AMCustomerMyCustomerGroupRequest class]]){
        if ([objects count]==0) {
            return;
        }
        AMCustomerMyCustomerGroupResult *result = (AMCustomerMyCustomerGroupResult*)[objects objectAtIndex:0];
    
         
        if(_categoryPicker){
            [_categoryPicker removeFromSuperview];
            self.categoryPicker = nil;
        }
        if(_areaPicker){
            [_areaPicker removeFromSuperview];
            self.areaPicker = nil;
        }
        if (self.myCustomersGroupObjects==nil) {
            
            NSArray *groupTemp = result.groupList;
            AMCustomerMyCustomerGroupListResult *groupResult = [groupTemp objectAtIndex:0];
            self.myCustomersGroupObjects = [[NSMutableArray alloc]initWithArray:groupResult.resultList];
        }
        
        if (self.myCustomersAreaObjects==nil) {
            
            NSArray *areaTemp = result.areaList;
            AMCustomerMyCustomerGroupListResult *areaResult = [areaTemp objectAtIndex:0];
            self.myCustomersAreaObjects = [[NSMutableArray alloc]initWithArray:areaResult.resultList];
            
        }
        
        [self.view addSubview:self.categoryPicker];
        [self.view addSubview:self.areaPicker];
//        }
   
    }else {

        
        AMCustomerMyCustomerResult *result = (AMCustomerMyCustomerResult*)[objects objectAtIndex:0];
        self.totalCount = result.totalCount;
        
        isLoading = NO;
        if (currentMyCustomerPage* DEFAULT_PAGE_SIZE >= [self.totalCount intValue]) {
            self.myCustomerTableView.tableFooterView = nil;
        }
        
        
       [self setTotalCustomerProperty:[NSString stringWithFormat:@"%d",[self.totalCount intValue]]];
        
        if (self.myCustomersObjects==nil||isNeedReload) {
            if(isNeedReload){
                if([self.myCustomersObjects count]>0){
                 [self.myCustomersObjects removeAllObjects];  
                    [myCustomerTableView reloadData];
                }
                isNeedReload = NO;
            }
            self.myCustomersObjects = [[NSMutableArray alloc]initWithArray:result.resultList];
            
        }
        else
        {
            if([result.resultList count]> 0){
                if (isPullViewLoad) {
                    [self.myCustomersObjects removeAllObjects];
                    isPullViewLoad = NO;
                }
                
                [self.myCustomersObjects addObjectsFromArray:result.resultList];
                
            }
            
        }
        
        myCustonerTotalCount=[result.totalCount intValue];
        [myCustomerTableView reloadData];
        [myCustomerTableView.pullToRefreshView performSelector:@selector(stopAnimating) withObject:nil];
        if (myCustonerTotalCount<=0) {
            [self showNodataMessage];
        }else {
            [self endLoadingView];
        }
        
        
        isLoading = NO;
    }
    
}
        

- (void)objectLoader:(RKObjectLoader*)objectLoader didFailWithError:(NSError*)error {
	NSLog(@"Hit error: %@", error);
    
    [myCustomerTableView.pullToRefreshView performSelector:@selector(stopAnimating) withObject:nil];
    
    [self.mLoadingView endLoadingView];
    if ([error code] == RKRequestBaseURLOfflineError||[error code] ==RKRequestConnectionTimeoutError||[error code] ==-1009){
        if(!isFromPicker){
            if (isPullViewLoad) {
                [self.myCustomerTableView.pullToRefreshView stopAnimating];
            }
            
            if ([self.myCustomersObjects count]) {
                AMErrorMessageView * errorMessageView = [[AMErrorMessageView alloc] init];
                self.myCustomerTableView.tableFooterView = errorMessageView;
                [errorMessageView release];
                if (!isPullViewLoad) {
                    currentMyCustomerPage--;
                }else {
                    currentMyCustomerPage = self.tempCurrentPage;
                    
                }
            }else {
                [self.mLoadingView showLoadFailedMessageForRequest:objectLoader];
            }
            isPullViewLoad = NO;
        }else{
            [self.mLoadingView showLoadFailedMessageForRequest:objectLoader];
            isFromPicker = NO;
        }
        
    }
    isLoading = NO;
    
    
    
//    if ([error code] == RKRequestBaseURLOfflineError||[error code] ==RKRequestConnectionTimeoutError||[error code] ==NSURLErrorConnectionToBeOffline)  {
//        [self.mLoadingView showLoadFailedMessageForRequest:objectLoader];
//    }
}

#pragma mark - View lifecycle
-(void)loadRequest
{
    NSString *loginUserName=nil;
    loginUserName=[LoginToken getLoginUserName];
     self.loginUserName = loginUserName;
    if ([loginUserName length] > 3) {
//        [self showLoadingView];

        if(self.myCustomerRequest==nil){
            self.myCustomerRequest = [[AMCustomerMyCustomerRequest alloc] init];
        }
        self.myCustomerRequest.pageIndex = [NSNumber numberWithInt: currentMyCustomerPage];
        [self loadObjectsFromRemoteMyCustomer];
    }    
} 

-(void)loadGroupRequest
{
    NSString *loginUserName=nil;
    loginUserName=[LoginToken getLoginUserName];
    self.loginUserName = loginUserName;
    if ([loginUserName length] > 3) {
//        [self showLoadingView];
        
        if(self.myCustomerGroupRequest==nil){
            self.myCustomerGroupRequest = [[AMCustomerMyCustomerGroupRequest alloc] init];
        }
//        self.myCustomerRequest.pageIndex = [NSNumber numberWithInt: currentMyCustomerPage];
        [self loadObjectsFromRemoteMyCustomerGroup];
    }    
} 

-(void)objManInit
{
    objMan = [[HJObjManager alloc] initWithLoadingBufferSize:6 memCacheSize:20];
    
    NSString* cacheDirectory = [NSHomeDirectory() stringByAppendingString:@"/Library/Caches/imgcachecustomer/"] ;
	HJMOFileCache* fileCache = [[[HJMOFileCache alloc] initWithRootPath:cacheDirectory] autorelease];
	objMan.fileCache = fileCache;
    // Have the file cache trim itself down to a size & age limit, so it doesn't grow forever
	fileCache.fileCountLimit = 100;
	fileCache.fileAgeLimit = 60*60*24*7; //1 week
	[fileCache trimCacheUsingBackgroundThread];
    
}

- (void)scrollViewDidScroll: (UIScrollView*)scroll {
    // UITableView only moves in one direction, y axis
    NSInteger currentOffset = scroll.contentOffset.y;
    NSInteger maximumOffset = scroll.contentSize.height - scroll.frame.size.height;

    // Change 10.0 to adjust the distance from bottom
    if (maximumOffset - currentOffset <= 100.0) {
        if (!isLoading) {
            
            if(currentMyCustomerPage* DEFAULT_PAGE_SIZE < myCustonerTotalCount) {
                currentMyCustomerPage++;
                [self loadRequest];
            }
          
            
        }
    }
}

#pragma mark - View lifecycle

- (void)viewDidLoad
{ 
    [super viewDidLoad];
    // Do any additional setup after loading the view from its nib.
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(loginEvent:) name:NOTIFICAGION_LOGIN_SUCC object:nil];
    
    [self objManInit];
    
    currentMyCustomerPage = 1;
    myCustonerTotalCount = 0;
    self.searchView.delegate = self;
    //    [self.searchView editBecomeFirstResponder];
    self.searchView.hidden= YES;

    if(_mMyCustomerSelectionView){
        [_mMyCustomerSelectionView removeFromSuperview];
    }
    [self.view addSubview:self.headerView];
//    [self.view addSubview:self.categoryPicker];
//    [self.view addSubview:self.areaPicker];
    
    [self.myCustomerTableView addPullToRefreshWithActionHandler:^{
        NSLog(@"refresh dataSource");
        myCustomerTableView.pullToRefreshView.lastUpdatedDate = [NSDate date]; 
        //        [myCustomerTableView.pullToRefreshView performSelector:@selector(stopAnimating) withObject:nil afterDelay:2];
        
//        [self clearData];
        self.myCustomerTableView.tableFooterView = nil;
        self.tempCurrentPage = currentMyCustomerPage;
        currentMyCustomerPage = 1;
        [self loadGroupRequest];
        [self loadRequest];
        isPullViewLoad = YES;
        //当用户上一次登陆恰好无数据的时候，切换到有数据的用户将出现loadingview无法出现的情况，原因是因为无数据的时候loadingView恰好被隐藏了
        if(self.mLoadingView.loadingView.hidden==NO){
            self.mLoadingView.loadingView.hidden = YES;
        }
        
    }];
    
    isTalkAfterWwLogin = NO;
}


- (void)viewDidUnload
{
//    _mLoadingView = nil;
    self.mLoadingView =nil;
    _searchView = nil;
    self.objMan = nil;
    if(_mMyCustomerSelectionView){
        [_mMyCustomerSelectionView removeFromSuperview];
        self.myCustomerTableView = nil;
    }
    self.allAreaDict = nil;
    self.allCategoryDict = nil;
    [_areaPicker release];
    [_categoryPicker release];
    _categoryPicker = nil;
    _areaPicker = nil;
    
    
    [self.myCustomersAreaObjects removeAllObjects];
    [self.myCustomersGroupObjects removeAllObjects];
    [self.myCustomersObjects removeAllObjects];
    self.myCustomersGroupObjects = nil;
    self.myCustomersAreaObjects = nil;
    self.myCustomersObjects = nil;
    self.myCustomerRequest = nil;
    self.myCustomerGroupRequest = nil;
    if(self.totalPreLabel){
        [self.totalPreLabel removeFromSuperview];
        self.totalPreLabel = nil;
    }
    if(self.totalMidLabel){
        [self.totalMidLabel removeFromSuperview];
        self.totalMidLabel = nil;
    }
    if(self.totalEndLabel){
        [self.totalEndLabel removeFromSuperview];
        self.totalEndLabel = nil;
    }
    self.buttonAllCategory= nil;
    self.buttonAllArea = nil;
    self.buttonQuickSearch = nil;
    self.cancelButton = nil;     
    
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
    
    [self loadRequestForFirstTime];
    
    if (isTalkAfterWwLogin) {
        [[NSNotificationCenter defaultCenter] removeObserver:self name:NOTIFICATION_WW_LOGIN_SUCC object:nil];
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(onWwLoginSucc) name:NOTIFICATION_WW_LOGIN_SUCC object:nil];
    }
}

- (void)viewWillDisappear:(BOOL)animated
{
	[super viewWillDisappear:animated];
    
    [[NSNotificationCenter defaultCenter] removeObserver:self name:NOTIFICATION_WW_LOGIN_SUCC object:nil];
}

- (void) clearData {
    
    //初始化两个按钮的状态
    [_buttonAllCategory setTitle:@"全部分组" forState:UIControlStateNormal];
    [_buttonAllArea setTitle:@"所有地区" forState:UIControlStateNormal];
    
    currentMyCustomerPage = 1;
    myCustonerTotalCount = 0;
    
    self.myCustomerRequest.groupId = nil;
    self.myCustomerRequest.province = nil;
    [self.myCustomersAreaObjects removeAllObjects];
    [self.myCustomersGroupObjects removeAllObjects];
    [self.myCustomersObjects removeAllObjects];
    self.myCustomersGroupObjects = nil;
    self.myCustomersAreaObjects = nil;
    self.myCustomersObjects = nil;
//    [self.myCustomerTableView reloadData];
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    // Return YES for supported orientations
    if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
        return (interfaceOrientation != UIInterfaceOrientationPortraitUpsideDown);
    } else {
        return YES;
    }
}


//这个方法告诉表格第section个分组有多少行
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section{
    
    return [self.myCustomersObjects count];
    
}

//设置cell高度
- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{ 
    return [AliTableViewCellMyCustomer cellHeight];  
}


- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath{
    
    NSUInteger row = [indexPath row];
    
    AliTableViewCellMyCustomer *cell = (AliTableViewCellMyCustomer *)[tableView dequeueReusableCellWithIdentifier: [AliTableViewCellMyCustomer cellIdentifer]];
    
    if (cell == nil)  {
        cell = [AliTableViewCellMyCustomer createCell];
    }
    
    AMCustomerMyCustomerListModel *myCustomer = (AMCustomerMyCustomerListModel*)[self.myCustomersObjects objectAtIndex:row ] ;
    cell.buyerName.text = myCustomer.customer.buyerName;
    if(!myCustomer.customer.province&&!myCustomer.customer.city){
        [cell.provinceAndCity setHidden:YES];
    }
    cell.provinceAndCity.text = [NSString stringWithFormat:@"%@%@",myCustomer.customer.province,myCustomer.customer.city];
    cell.corpName.text = myCustomer.customer.corpName;
    
    NSString *countValue = [NSString stringWithFormat:@"%d",[myCustomer.enquiryTotalTimes intValue]];
    
    [self setEnquiryTimesProperty:countValue rootCell:cell];
    
    cell.strLastEnquiryTime.text = [NSString stringWithFormat:@"最近一次 : %@",myCustomer.strLastEnquiryTime];
    
    cell.talkBtn.param = myCustomer;
    [cell.talkBtn addTarget:self action:@selector(talkAction:) forControlEvents:UIControlEventTouchUpInside];
    
    return cell;
}

- (void) setEnquiryTimesProperty:(NSString *)countValue rootCell:(AliTableViewCellMyCustomer *)cell{
    
    CGSize labelSizePre = [countValue sizeWithFont:[UIFont systemFontOfSize:14.0f]];
    UILabel *preLabel = [[UILabel alloc] initWithFrame:CGRectMake(0, 9, labelSizePre.width, labelSizePre.height)];
    preLabel.font = [UIFont systemFontOfSize:14.0f];
    preLabel.numberOfLines = 1;
    preLabel.lineBreakMode = UILineBreakModeWordWrap;
    preLabel.backgroundColor = [UIColor clearColor];
    preLabel.textColor = RGB(0xff,0x00,0x00);
    preLabel.highlightedTextColor = RGB(0xff,0x00,0x00);
    preLabel.text = countValue;
    [cell.enquiryTotalTimes addSubview:preLabel];
    
    CGSize labelSize = [@"次" sizeWithFont:[UIFont systemFontOfSize:14.0f]];
    UILabel *midLabel = [[UILabel alloc] initWithFrame:CGRectMake(preLabel.frame.size.width, 9, labelSize.width, labelSize.height)];
    midLabel.font = [UIFont systemFontOfSize:14.0f];
    midLabel.numberOfLines = 1;
    midLabel.lineBreakMode = UILineBreakModeWordWrap;
    midLabel.backgroundColor = [UIColor clearColor];
    midLabel.textColor = RGB(0x66,0x66,0x66);
    midLabel.highlightedTextColor = RGB(0x66,0x66,0x66);
    midLabel.text = @"次";
    [cell.enquiryTotalTimes addSubview:midLabel];
    
    [preLabel release];
    [midLabel release];
}

- (IBAction)talkAction:(id)sender {
    [AMLogUtils appendLog:CUSTOMERMANAGER_MYCUSTOMER_EIGHT];
    AMCustomerMyCustomerListModel * costomerMode = ((AliParamButton *)sender).param;
    if (costomerMode == nil || costomerMode.customer == nil || costomerMode.customer.memberId == nil) {
        [[AliToastView MakeToastWithType:TOAST_STYLE_COMMON info:NSLocalizedString(@"TALK_ERROR_NOT_REG_MEMBER", @"")] show];
    } else {
        contactName = costomerMode.customer.buyerName;
        contactId = costomerMode.customer.memberId;
        
        if([LoginToken isWangWangLogined]) {
            AMIMTalkViewController * talkViewController = [[AMIMTalkViewController alloc] initWithParam:NO:NO:nil:costomerMode.customer.memberId : costomerMode.customer.buyerName];
            [talkViewController setHidesBottomBarWhenPushed:YES];
            [self.mNavigationController pushViewController:talkViewController animated:YES];
            [talkViewController release];
        } else {
            isTalkAfterWwLogin = YES;
            [[NSNotificationCenter defaultCenter] removeObserver:self name:NOTIFICATION_WW_LOGIN_SUCC object:nil];
            [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(onWwLoginSucc) name:NOTIFICATION_WW_LOGIN_SUCC object:nil];
            
            [[NSNotificationCenter defaultCenter] postNotificationName:NOTIFICATION_DO_WW_LOGIN object:nil];
        }
    }
}

//单击行
- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath{
    [AMLogUtils appendLog:CUSTOMERMANAGER_MYCUSTOMER_TEN];
    AMCustomerMyCustomerListModel *myCustomer = [self.myCustomersObjects objectAtIndex:indexPath.row];
    NSString * buyerId = myCustomer.customer.buyerId;
    AMCustomerInfoViewController * infoController = [[[AMCustomerInfoViewController alloc] initWithBuyerId:buyerId] autorelease];
    [self.mNavigationController pushViewController:infoController animated:YES];
    [self.myCustomerTableView deselectRowAtIndexPath:indexPath animated:NO];
}

-(void)onWwLoginSucc {
    if (isTalkAfterWwLogin) {
        AMIMTalkViewController * talkViewController = [[AMIMTalkViewController alloc] initWithParam:NO:NO:nil:contactId : contactName];
        [talkViewController setHidesBottomBarWhenPushed:YES];
        [self.mNavigationController pushViewController:talkViewController animated:YES];
        [talkViewController release];
    }
    
    isTalkAfterWwLogin = false;
}

-(void)loginEvent:(id)sender{
    [self clearData];
    [self loadGroupRequest];
    [self loadRequest];
    //当用户上一次登陆恰好无数据的时候，切换到有数据的用户将出现loadingview无法出现的情况，原因是因为无数据的时候loadingView恰好被隐藏了
    if(self.mLoadingView.loadingView.hidden==YES){
        self.mLoadingView.loadingView.hidden = NO;
    }
    
}
- (void)dealloc {
    [[NSNotificationCenter defaultCenter] removeObserver:self];
    
    [myCustomerTableView release];
    [_myCustomersObjects release];
    [_myCustomersGroupObjects release];
    [_myCustomersAreaObjects release];
    [_myCustomerRequest release];
    [_myCustomerGroupRequest release];
    [objMan release];
//    [_mLoadingView release];
    self.mLoadingView = nil;
    [_loginUserName release];
    [_headerView release];
    [_buttonAllCategory release];
    [_buttonAllArea release];
    [_buttonQuickSearch release];
    [_areaPicker release];
    [_categoryPicker release];
    [_cancelButton release];                    
    [_mMyCustomerSelectionView release];
    [_allAreaDict release];
    [_allCategoryDict release];
    [_totalCount release];
    [_totalCountLabel release];
    [_totalMidLabel release];
    [_totalEndLabel release];
    [_totalPreLabel release];
    [contactName release];
    [contactId release];
    [super dealloc];
}

- (void)OceanClient:(RKOceanClient *)oceanClient didRefreshTokenOutOfDate:(RKResponse *)response{
    [super OceanClient:oceanClient didRefreshTokenOutOfDate:response];
    [self.mLoadingView showNodataMessage];
    [[AliToastView MakeToastWithType:TOAST_STYLE_COMMON info:@"鉴权失败"] show]; 

    UIViewController *nextController;
    nextController = [[[AMIMViewController alloc] initWithNibName:@"AMIMViewController_iPhone" bundle:nil] autorelease];
    nextController.hidesBottomBarWhenPushed=YES;
    
    [self.mNavigationController pushViewController:nextController animated:YES];
}

- (void)OceanClient:(RKOceanClient *)oceanClient didDonotLogin:(RKResponse *)response{
    [super OceanClient:oceanClient didDonotLogin:response];
    [self.mLoadingView showNodataMessage];
    [[AliToastView MakeToastWithType:TOAST_STYLE_COMMON info:@"请您重新登陆"] show]; 
}
-(void)loadRequestForFirstTime
{
    
    if (self.isFirstLoadView) {
        NSString *name = [LoginToken getLoginUserName];
        if(name!=nil&&[name length]>3){
            [self loadGroupRequest];
            [self loadRequest];
            self.isFirstLoadView = NO;
        }
    }
}



//-(void)reloadLoadingData{
//    [self loadGroupRequest];
//    [self loadRequest];
//}
@end
