

#import "AMOrderStateRightViewController.h"
#import "AliTableViewCellCategory.h"
#import "AMOrderManageHomeViewController.h"
#import "LoginToken.h"
#import "AMLogiticsViewController.h"
#import "AMAppDelegate.h"

#define RGB(r, g, b) [UIColor colorWithRed:r/255.0 green:g/255.0 blue:b/255.0 alpha:1.0]

@implementation AMOrderStateRightViewController

@synthesize headerView = _headerView;
@synthesize orderStateTableView = _orderStateTableView;
@synthesize sourceData = _sourceData;
@synthesize selectedItem = _selectedItem;
@synthesize mTableView = _mTableView;

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
                       [NSDictionary dictionaryWithObjectsAndKeys:@"所有状态", @"content",@"", @"requestKey",nil],
                       [NSDictionary dictionaryWithObjectsAndKeys:@"等待买家付款的订单", @"content",@"waitbuyerpay", @"requestKey",nil],
                       [NSDictionary dictionaryWithObjectsAndKeys:@"等待卖家发货的订单", @"content",@"waitsellersend", @"requestKey",nil],
                       [NSDictionary dictionaryWithObjectsAndKeys:@"等待买家收货的订单", @"content",@"waitbuyerreceive", @"requestKey",nil],
                       [NSDictionary dictionaryWithObjectsAndKeys:@"交易成功的订单", @"content",@"success", @"requestKey",nil],
                       [NSDictionary dictionaryWithObjectsAndKeys:@"交易关闭的订单", @"content",@"cancel", @"requestKey",nil],
                       nil ];
    }
    return _sourceData;
}

-(UIView*)headerView
{
    if (!_headerView) {
        _headerView = [[UIView alloc]initWithFrame:CGRectMake(0.0, 0.0, 320.0, 40.0)];
        _headerView.backgroundColor = RGB(0x44, 0x44, 0x44);
        
        NSString * preString = [NSString stringWithFormat:@"近三个月订单"];
        CGSize labelSizePre = [preString sizeWithFont:[UIFont systemFontOfSize:14.0f]];
        UILabel *preLabel = [[UILabel alloc] initWithFrame:CGRectMake(15, 0, labelSizePre.width, 40.0)];
        preLabel.font = [UIFont systemFontOfSize:14.0f];
        preLabel.numberOfLines = 1;
        preLabel.lineBreakMode = UILineBreakModeWordWrap;
        preLabel.backgroundColor = [UIColor clearColor];
        preLabel.textColor = RGB(0x66,0x66,0x66);
        preLabel.highlightedTextColor = RGB(0x66,0x66,0x66);
        preLabel.text = preString;
        [_headerView addSubview:preLabel];
     
        [preLabel release];
        
    }
    return _headerView;
}


#pragma mark - Lifecycle

- (void)viewDidLoad {
//    [self.view addSubview:self.headerView];
    UIImage * listBgImage =  [UIImage imageNamed:@"or_sx_bg_02"];
    listBgImage = [listBgImage stretchableImageWithLeftCapWidth:listBgImage.size.width/2 topCapHeight:listBgImage.size.height/2];
     UIImageView *imageView = [[UIImageView alloc] initWithImage:listBgImage];
    self.mTableView.backgroundView = imageView;
    [imageView release];
//    self.mTableView.backgroundColor = [UIColor colorWithPatternImage:listBgImage];
    [super viewDidLoad];
}

- (void)viewDidUnload {
    [tableTitles release];
    tableTitles = nil;
    [super viewDidUnload];
}

- (void)dealloc {
    [tableTitles release];
    [_headerView release];
    [_orderStateTableView release];
    [_sourceData release];
    [_mTableView release];
    [super dealloc];
}

#pragma mark - Public

- (void)setVisible:(BOOL)visible {
    self.view.hidden = !visible;
}

#pragma mark - UITableView delegate

// Called after the user changes the selection.
- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    NSUInteger row = [indexPath row];
    NSDictionary *dictMapValues = [_sourceData objectAtIndex:row];
    NSString *requestKey  =[dictMapValues objectForKey:@"requestKey"];
    NSLog(@"request key = %@",requestKey);
    self.selectedItem = row;
    [tableView reloadData];
    [tableView deselectRowAtIndexPath:indexPath animated:NO];
    [[NSNotificationCenter defaultCenter] postNotificationName:NOTIFICATION_ORDER_STATE object:requestKey];
    
    
}

#pragma mark - UITableView datasource

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return [self.sourceData count];
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    return [AliTableViewCellCategory cellHeight];
}

- (UITableViewCell *)tableView:(UITableView *)tableView
         cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    tableView.separatorStyle  = UITableViewCellSeparatorStyleNone;
    
    
    AliTableViewCellCategory *cell = (AliTableViewCellCategory *)[tableView dequeueReusableCellWithIdentifier: [AliTableViewCellCategory cellIdentifer]];
    if (cell == nil)
    {
        cell = [AliTableViewCellCategory createCell];
    }
    
    UIView *view = [[UIView alloc] initWithFrame:cell.frame];
    UIImage * listBgImage =  [UIImage imageNamed:@"or_sx_bg"];
    listBgImage = [listBgImage stretchableImageWithLeftCapWidth:listBgImage.size.width/2 topCapHeight:listBgImage.size.height/2];
    view.backgroundColor = [UIColor colorWithPatternImage:listBgImage];
//    listbg.image = listBgImage;
//    cellBackBtn.image =listBgImage;
    
//    self.selectedBackgroundView = cellBackBtn;
//    [cellBackBtn release];
//    cell.backgroundView = 
//    [listbg release];
    cell.backgroundView = view;
    [view release];
    NSUInteger row = [indexPath row];
    NSDictionary *dictMapValues = [_sourceData objectAtIndex:row];
    cell.title.text =[dictMapValues objectForKey:@"content"];
    cell.title.fontSize = 16.0f;
    cell.title.textColor = RGB(0xab, 0xab, 0xab);
//    cell.identifyImage.image = [UIImage imageNamed:@"icon_history"];
    cell.identifyImage.frame = CGRectMake(230, 14, 16, 16);
    cell.identifyImage.image = [UIImage imageNamed:@"or_check"]; 
    if(row==self.selectedItem){
        cell.identifyImage.hidden = NO;
    }else{
        cell.identifyImage.hidden = YES;
    }
    return cell;
}

@end
