//
//  AMCompanySelectViewController.m
//  AlibabaMobile
//
//  Created by zzh on 12-1-5.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMCompanySelectViewController.h"

#import <RestKit/RestKit.h>
#import "AMCorporation.h"
#import "AMCorpsByLetter.h"
#import "AMLogiticsData.h"
#import "AliTitleCellView.h"
#import "AMLogTypeCode.h"
#import "AMLogUtils.h"
#import "AliTableViewCellCategory.h"
const NSString *gLogisticsCorpsJson = @"{\"letterCorps\":[{\"corps\":[{\"pinyin\":\"dbwl\",\"name\":\"德邦物流\",\"code\":\"DEPPON\"},{\"pinyin\":\"xbwl\",\"name\":\"新邦物流\",\"code\":\"XBWL\"},{\"pinyin\":\"ttkd\",\"name\":\"天天快递\",\"code\":\"TTKDEX\"},{\"pinyin\":\"tdhy\",\"name\":\"天地华宇\",\"code\":\"HOAU\"},{\"pinyin\":\"jjky\",\"name\":\"佳吉快运\",\"code\":\"JIAJI\"},{\"pinyin\":\"dtly\",\"name\":\"大田陆运\",\"code\":\"DTW\"},{\"pinyin\":\"sfsy\",\"name\":\"顺丰速运\",\"code\":\"SFEXPRESS\"},{\"pinyin\":\"stkd\",\"name\":\"申通快递\",\"code\":\"STO\"},{\"pinyin\":\"ytsd\",\"name\":\"圆通速递\",\"code\":\"YTO\"},{\"pinyin\":\"ydky\",\"name\":\"韵达快运\",\"code\":\"YUNDA\"},{\"pinyin\":\"ztsd\",\"name\":\"中通速递\",\"code\":\"ZTO\"},{\"pinyin\":\"ems\",\"name\":\"EMS\",\"code\":\"EMS\"}],\"key\":\"热门\"},{\"corps\":[{\"pinyin\":\"ajkd\",\"name\":\"安捷快递\",\"code\":\"ANJELEX\"},{\"pinyin\":\"axd\",\"name\":\"安信达\",\"code\":\"ANXINDA\"},{\"pinyin\":\"aae\",\"name\":\"AAE\",\"code\":\"AAEWEB\"}],\"key\":\"A\"},{\"corps\":[{\"pinyin\":\"bjkd\",\"name\":\"彪记快递\",\"code\":\"PEWKEE\"},{\"pinyin\":\"bfdf\",\"name\":\"百福东方\",\"code\":\"EES\"}],\"key\":\"B\"},{\"corps\":[{\"pinyin\":\"cces\",\"name\":\"CCES\",\"code\":\"CCES\"}],\"key\":\"C\"},{\"corps\":[{\"pinyin\":\"dbwl\",\"name\":\"德邦物流\",\"code\":\"DEPPON\"},{\"pinyin\":\"dtly\",\"name\":\"大田陆运\",\"code\":\"DTW\"},{\"pinyin\":\"dskd\",\"name\":\"D速快递\",\"code\":\"DEXP\"},{\"pinyin\":\"dpex\",\"name\":\"DPEX\",\"code\":\"DPEX\"},{\"pinyin\":\"dhl \",\"name\":\"DHL \",\"code\":\"DHL\"}],\"key\":\"D\"},{\"corps\":[{\"pinyin\":\"ems\",\"name\":\"EMS\",\"code\":\"EMS\"}],\"key\":\"E\"},{\"corps\":[{\"pinyin\":\"fhkd\",\"name\":\"凤凰快递\",\"code\":\"PHOENIXEXP\"},{\"pinyin\":\"fkd\",\"name\":\"飞康达\",\"code\":\"FKD\"},{\"pinyin\":\"fedex\",\"name\":\"FedEx\",\"code\":\"FEDEX\"}],\"key\":\"F\"},{\"corps\":[{\"pinyin\":\"glskd\",\"name\":\"GLS快递\",\"code\":\"CNGLS\"},{\"pinyin\":\"gznd\",\"name\":\"港中能达\",\"code\":\"ND56\"},{\"pinyin\":\"gdyz\",\"name\":\"广东邮政\",\"code\":\"GDEMS\"}],\"key\":\"G\"},{\"corps\":[{\"pinyin\":\"htky\",\"name\":\"汇通快运\",\"code\":\"HTKY\"},{\"pinyin\":\"hlwl\",\"name\":\"恒路物流\",\"code\":\"HENGLU\"},{\"pinyin\":\"hhkd\",\"name\":\"华慧快递\",\"code\":\"BHTEXP\"},{\"pinyin\":\"hxl\",\"name\":\"华夏龙\",\"code\":\"CHINADRAGON\"}],\"key\":\"H\"},{\"corps\":[{\"pinyin\":\"jjky\",\"name\":\"佳吉快运\",\"code\":\"JIAJI\"},{\"pinyin\":\"jgsd\",\"name\":\"京广速递\",\"code\":\"KKE\"},{\"pinyin\":\"jywl\",\"name\":\"佳怡物流\",\"code\":\"JIAYI\"},{\"pinyin\":\"jxd\",\"name\":\"急先达\",\"code\":\"JOUST\"},{\"pinyin\":\"jym\",\"name\":\"加运美\",\"code\":\"TMS\"}],\"key\":\"J\"},{\"corps\":[{\"pinyin\":\"kjsd\",\"name\":\"快捷速递\",\"code\":\"FASTEXPRESS\"}],\"key\":\"K\"},{\"corps\":[{\"pinyin\":\"lbkd\",\"name\":\"蓝镖快递\",\"code\":\"BLUEDART\"},{\"pinyin\":\"lbwl\",\"name\":\"龙邦物流\",\"code\":\"LBEX\"},{\"pinyin\":\"lht\",\"name\":\"联昊通\",\"code\":\"LTS\"}],\"key\":\"L\"},{\"corps\":[{\"pinyin\":\"mhkd\",\"name\":\"民航快递\",\"code\":\"CAE\"}],\"key\":\"M\"},{\"corps\":[{\"pinyin\":\"pshy\",\"name\":\"配思货运\",\"code\":\"PEISI\"}],\"key\":\"P\"},{\"corps\":[{\"pinyin\":\"qckd\",\"name\":\"全晨快递\",\"code\":\"QCKD\"},{\"pinyin\":\"qykd\",\"name\":\"全一快递\",\"code\":\"APEX\"},{\"pinyin\":\"qrt\",\"name\":\"全日通\",\"code\":\"ATEXPRESS\"},{\"pinyin\":\"qjt\",\"name\":\"全际通\",\"code\":\"QUANJT\"}],\"key\":\"Q\"},{\"corps\":[{\"pinyin\":\"shwl\",\"name\":\"盛辉物流\",\"code\":\"SHENGHUI\"},{\"pinyin\":\"stkd\",\"name\":\"申通快递\",\"code\":\"STO\"},{\"pinyin\":\"sfwl\",\"name\":\"盛丰物流\",\"code\":\"SFWL\"},{\"pinyin\":\"sewl\",\"name\":\"速尔物流\",\"code\":\"SURE\"},{\"pinyin\":\"sfsy\",\"name\":\"顺丰速运\",\"code\":\"SFEXPRESS\"},{\"pinyin\":\"sdwl\",\"name\":\"上大物流\",\"code\":\"SUNDAPOST\"}],\"key\":\"S\"},{\"corps\":[{\"pinyin\":\"ttkd\",\"name\":\"天天快递\",\"code\":\"TTKDEX\"},{\"pinyin\":\"tdhy\",\"name\":\"天地华宇\",\"code\":\"HOAU\"},{\"pinyin\":\"tnt\",\"name\":\"TNT\",\"code\":\"TNT\"}],\"key\":\"T\"},{\"corps\":[{\"pinyin\":\"ups\",\"name\":\"UPS\",\"code\":\"UPS\"}],\"key\":\"U\"},{\"corps\":[{\"pinyin\":\"wysd\",\"name\":\"伍圆速递\",\"code\":\"F5XM\"},{\"pinyin\":\"wjhk\",\"name\":\"文捷航空\",\"code\":\"GZWENJIE\"},{\"pinyin\":\"wxwl\",\"name\":\"万象物流\",\"code\":\"EWINSHINE\"},{\"pinyin\":\"wjwl\",\"name\":\"万家物流\",\"code\":\"MANCO\"}],\"key\":\"W\"},{\"corps\":[{\"pinyin\":\"xbwl\",\"name\":\"新邦物流\",\"code\":\"XBWL\"},{\"pinyin\":\"xcjb\",\"name\":\"星晨急便\",\"code\":\"STARS\"},{\"pinyin\":\"xfwl\",\"name\":\"信丰物流\",\"code\":\"XFEXPRESS\"},{\"pinyin\":\"xfh\",\"name\":\"鑫飞鸿\",\"code\":\"XFHEX\"}],\"key\":\"X\"},{\"corps\":[{\"pinyin\":\"ytsd\",\"name\":\"圆通速递\",\"code\":\"YTO\"},{\"pinyin\":\"ydky\",\"name\":\"韵达快运\",\"code\":\"YUNDA\"},{\"pinyin\":\"ytkd\",\"name\":\"运通快递\",\"code\":\"YTEXPRESS\"},{\"pinyin\":\"yfwl\",\"name\":\"越丰物流\",\"code\":\"YFEXPRESS\"},{\"pinyin\":\"ycwl\",\"name\":\"远成物流\",\"code\":\"YCGWL\"},{\"pinyin\":\"yfsd\",\"name\":\"亚风速递\",\"code\":\"BROADASIA\"},{\"pinyin\":\"ybsd\",\"name\":\"一邦速递\",\"code\":\"EBONEXP\"},{\"pinyin\":\"yswl\",\"name\":\"优速物流\",\"code\":\"UC56\"},{\"pinyin\":\"yzjc\",\"name\":\"元智捷诚\",\"code\":\"YJKD\"},{\"pinyin\":\"yfh\",\"name\":\"原飞航\",\"code\":\"YFHEX\"},{\"pinyin\":\"yad\",\"name\":\"源安达\",\"code\":\"YADEX\"},{\"pinyin\":\"ywf\",\"name\":\"源伟丰\",\"code\":\"YWFEX\"}],\"key\":\"Y\"},{\"corps\":[{\"pinyin\":\"ztsd\",\"name\":\"中通速递\",\"code\":\"ZTO\"},{\"pinyin\":\"ztky\",\"name\":\"中铁快运\",\"code\":\"CRE\"},{\"pinyin\":\"zjs\",\"name\":\"宅急送\",\"code\":\"ZJS\"},{\"pinyin\":\"zgdf\",\"name\":\"中国东方\",\"code\":\"COE\"},{\"pinyin\":\"zywl\",\"name\":\"中邮物流\",\"code\":\"CNPL\"}],\"key\":\"Z\"}]}";

#define RGB(r, g, b) [UIColor colorWithRed:r/255.0 green:g/255.0 blue:b/255.0 alpha:1.0]
@interface AMCompanySelectViewController()
@property (readwrite,nonatomic) BOOL isSearching;
@property (nonatomic,retain) NSMutableArray *companyGroupList;
@property (nonatomic,retain) NSMutableArray *searchResultCopy;
-(void)resetSearch;
-(void)refreshInputState;
@end

@implementation AMCompanySelectViewController
@synthesize inputBg=_inputBg;
@synthesize deleteButton = _deleteButton;
@synthesize cancelButton = _cancelButton;
@synthesize searchField = _searchField;
@synthesize searchSelectTable = _searchSelectTable;
@synthesize companyGroupList=_companyGroupList;
@synthesize isSearching = _isSearching;
@synthesize searchResultCopy=_searchResultCopy;
-(NSMutableArray*)companyGroupList
{
    if (_companyGroupList==nil) {
        _companyGroupList = [[NSMutableArray alloc] init];
        
        NSString* MIMEType = @"application/json";
        NSError* error = nil;
        id<RKParser> parser = [[RKParserRegistry sharedRegistry] parserForMIMEType:MIMEType];
        id parsedData = [parser objectFromString:(NSString*)gLogisticsCorpsJson error:&error];
        if (parsedData == nil && error) {
           
        }
        else {
            // Setup object mapping
            RKObjectMappingProvider* mappingProvider = [RKObjectManager sharedManager].mappingProvider;
            [mappingProvider setMapping:[AMCorpsByLetter sharedObjectMapping] forKeyPath:@"letterCorps"];
            
            RKObjectMapper* mapper = [RKObjectMapper mapperWithObject:parsedData mappingProvider:mappingProvider];
            RKObjectMappingResult* result = [mapper performMapping];
            if (result) {
                [_companyGroupList addObjectsFromArray:[result asCollection]];
                
            }

        }
    }
    return _companyGroupList;
}

-(NSMutableArray*)searchResultCopy
{
    if (_searchResultCopy==nil) {
        _searchResultCopy = [[NSMutableArray alloc] init];
    }
    return _searchResultCopy;
}

- (void)dealloc {
    [_inputBg release];
    [_deleteButton release];
    [_cancelButton release];
    [_searchField release];
    [_searchSelectTable release];
    [_companyGroupList release];
    [_searchResultCopy release];
    [super dealloc];
}
- (void)viewDidUnload {
    [self setInputBg:nil];
    [self setDeleteButton:nil];
    [self setCancelButton:nil];
    [self setSearchField:nil];
    [self setSearchSelectTable:nil];
    _companyGroupList = nil;
    _searchResultCopy = nil;
    [super viewDidUnload];
}
-(void)viewDidLoad
{
    AliNavigationBackButton *button = [[[AliNavigationBackButton alloc] initWithTitle:@"取消"] autorelease];
    button.navigationBackDelegate = self;
    self.navigationItem.leftBarButtonItem = button;
    //[button release];
    
    self.navigationItem.title=@"选择物流公司";
    self.isSearching = NO;
    
    
    [super viewDidLoad];
    self.cancelButton.hidden = NO;
}
- (void) navigationBack
{
    [self.navigationController popViewControllerAnimated:YES];
}
- (IBAction)deleteButtonPressed {
    self.searchField.text=@"";
    [self resetSearch];
    [self.searchSelectTable reloadData];
    [self.searchSelectTable resignFirstResponder];

}
- (IBAction)canncelButtonPressed {
    self.searchField.text=@"";
    [self.searchField resignFirstResponder];
   
    [UIView setAnimationDuration:0.4];
    [UIView beginAnimations:@"scale" context:nil];
    
    self.inputBg.frame=CGRectMake(10, 0, 300, 44);
    self.searchField.frame = CGRectMake(49, 6, 300, 31);
//    [self.cancelButton setHidden:YES];
    self.cancelButton.frame = CGRectMake(334, 0, 60, 44);
    [self.deleteButton setHidden:YES];
    [self.navigationController setNavigationBarHidden:NO animated:YES];
    
    [UIView commitAnimations];

}
- (IBAction)searchEditBegin {
    
    [self resetSearch];
    [self.searchSelectTable reloadData];
    [self.searchSelectTable resignFirstResponder];
    
    [UIView setAnimationDuration:0.4];
    [UIView beginAnimations:@"scale" context:nil];
    
    self.inputBg.frame=CGRectMake(10, 0, 248, 44);
    self.searchField.frame = CGRectMake(49, 6, 248, 31);
//    [self.cancelButton setHidden:NO];
    self.cancelButton.frame = CGRectMake(258, 0, 60, 44);
    [self.navigationController setNavigationBarHidden:YES animated:YES];

    [UIView commitAnimations];
    
}
- (IBAction)searchContentEditChange {

    if ([self.searchField.text length]==0) {
        self.isSearching = NO;
        [self resetSearch];
        [self.searchSelectTable reloadData];
        [self refreshInputState];
            return;
    }
    self.isSearching = YES;
    [self handleSearchForTerm:self.searchField.text];
    [self refreshInputState];

}

#pragma Table View Data 

-(void)resetSearch
{
    
    NSMutableArray *array =[[NSMutableArray alloc]init];
    int num = [self.companyGroupList count];
    for (int index=1; index<num; index++) {
        AMCorpsByLetter *group =(AMCorpsByLetter*)[self.companyGroupList objectAtIndex:index];
        [array addObjectsFromArray:group.corps];
    }
    
    [self.searchResultCopy removeAllObjects];
    [self.searchResultCopy addObjectsFromArray:array];
    [array release];

}

-(void)refreshInputState
{
    if (self.searchField.text==nil||self.searchField.text.length ==0) {
        
        [self.deleteButton setHidden:YES];
         self.searchField.frame = CGRectMake(49, 6, 248, 31);
        
    }
    else
    {
        [self.deleteButton setHidden:NO];
         self.searchField.frame = CGRectMake(49, 6, 218, 31);
    }
}

-(void)handleSearchForTerm:(NSString *)searchTerm
{         
    
    [self resetSearch];
    NSMutableArray *remove =[[NSMutableArray alloc]init];
    for (AMCorporation*cop in self.searchResultCopy)
    {
        if ([cop.pinyin rangeOfString:searchTerm options:NSCaseInsensitiveSearch].location==NSNotFound&&[cop.name rangeOfString:searchTerm options:NSCaseInsensitiveSearch].location==NSNotFound)
        {
            [remove addObject:cop];
        }
       
    }
    [self.searchResultCopy removeObjectsInArray:remove];
    [remove release];
    [self.searchSelectTable reloadData];}

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
   
    if (self.isSearching) {
        return 1;
    }
    return [self.companyGroupList count];
}


-(NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    if (self.isSearching) {
        return [self.searchResultCopy count];
    }
    AMCorpsByLetter *group =(AMCorpsByLetter*)[self.companyGroupList objectAtIndex:section];
    return [group.corps count];
    
}


-(UITableViewCell*)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    NSUInteger section = [indexPath section];
    NSUInteger row = [indexPath row];
      AliTableViewCellCategory *cell = (AliTableViewCellCategory *)[tableView dequeueReusableCellWithIdentifier: [AliTableViewCellCategory cellIdentifer]];
    if (cell == nil)  
    {
        cell = [AliTableViewCellCategory createCell];
        cell.identifyImage.image=nil;
    }
   
    if (self.isSearching) {
        cell.title.text = [[self.searchResultCopy objectAtIndex:row] name];
        
    }
    else
    {
        AMCorpsByLetter *group =(AMCorpsByLetter*)[self.companyGroupList objectAtIndex:section];
        cell.title.text = [[group.corps objectAtIndex:row] name];
    }
    return cell;
}

- (CGFloat)tableView:(UITableView *)tableView heightForHeaderInSection:(NSInteger)section
{
    if(tableView == self.searchSelectTable){
        return 25;
    }
    return 0;
}

- (UIView *)tableView:(UITableView *)tableView viewForHeaderInSection:(NSInteger)section
{
    if(tableView == self.searchSelectTable){
        AliTitleCellView * titleView = [[[AliTitleCellView alloc] initWithFrame:CGRectMake(0, 0, 320, 25)] autorelease];
        
        if (!self.isSearching) {
            AMCorpsByLetter *group =(AMCorpsByLetter*)[self.companyGroupList objectAtIndex:section];
            
            [titleView setTitle:group.key];
        }
        
        return  titleView;
    }
    return nil;
}

- (void)tableView:(UITableView *)tableView 
didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    
    [AMLogUtils appendLog: APP_LOGISTICS_NINE]; 
    NSUInteger section = [indexPath section];
    NSUInteger row = [indexPath row];
    
    AMLogiticsData *data = [[AMLogiticsData alloc]init];
    if (self.isSearching) 
    {
        data.data = [self.searchResultCopy objectAtIndex:row];
        // [data saveLastCompanyData:[companyCopy objectAtIndex:row]];
    }
    else
    {
        AMCorpsByLetter *group =(AMCorpsByLetter*)[self.companyGroupList objectAtIndex:section];
        data.data = [group.corps objectAtIndex:row];
        // [data saveLastCompanyData:[group.corps objectAtIndex:row]];
    }
    [data release];
    [self.navigationController setNavigationBarHidden:NO animated:YES];

    [self.navigationController popViewControllerAnimated:YES];
    
}
@end
