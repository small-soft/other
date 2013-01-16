//
//  AMGraphPickView.m
//  AlibabaMobile
//
//  Created by cloud ma on 12-7-17.
//  Copyright (c) 2012年 alibaba. All rights reserved.
//

#import "AMGraphPickView.h"
#import "UIHelp.h"
#import "StringUtils.h"
//navigation title font size
extern const float NAV_TITLE_FONT_SIZE;

//navigation title color
extern const int NAV_TITLE_FONT_COLOR;

//navigation title max characters num
extern const int NAV_TITLE_MAX_CHARS_NUM;

@implementation AMGraphPickView
@synthesize mGraphTimeTypeTableView = _mGraphTimeTypeTableView,mGraphTimeTypeSelectionView = _mGraphTimeTypeSelectionView,lableTimeType = _lableTimeType,lableTitle = _lableTitle,mSelectTypeButtonUp=_mSelectTypeButtonUp,mSelectTypeButtonDown=_mSelectTypeButtonDown, mGraphFilter=_mGraphFilter,mGraphTimeDict=_mGraphTimeDict, dataSource=_dataSource;
@synthesize lastIndex;

+(id)createView
{
    NSArray *nib = [[NSBundle mainBundle] loadNibNamed:@"AMGraphPickView" 
                                                 owner:self options:nil];
    for (id oneObject in nib)
    {
        if ([oneObject isKindOfClass:[AMGraphPickView class]])
        {
            AMGraphPickView *obj = (AMGraphPickView *)oneObject;
            [obj initView];
            return obj;
        }
    }
    return nil;
}
-(void) initView
{
    if (self.mGraphTimeDict == nil) {
        NSArray *mGraphTimeDictTmp = [[NSArray alloc] initWithObjects:@"年度", @"一季",@"一月",@"一周",nil];
        self.mGraphTimeDict = mGraphTimeDictTmp;
        [mGraphTimeDictTmp release];
    }
    self.mGraphFilter = 0;
    self.lastIndex = 0;
    
    //self.lableTitle.text = [NSString stringWithFormat:@""];
    self.lableTitle.textColor = [UIColor whiteColor];
    self.lableTitle.font = [UIFont boldSystemFontOfSize:NAV_TITLE_FONT_SIZE];
    self.lableTitle.shadowColor = [UIColor blackColor];
    self.lableTitle.shadowOffset = CGSizeMake(0, -1);
    self.lableTitle.text = [StringUtils makeTitleFromString:@"" ofLength:NAV_TITLE_MAX_CHARS_NUM];
    [self sizeToFit];

    self.lableTimeType.text = [NSString stringWithFormat:@"(%@)",[self.mGraphTimeDict objectAtIndex:self.mGraphFilter]];
    self.lableTimeType.textColor = [UIColor whiteColor];
    self.lableTimeType.font = [UIFont boldSystemFontOfSize:12.0f];
    self.lableTimeType.shadowColor = [UIColor blackColor];
    self.lableTimeType.shadowOffset = CGSizeMake(0, -1);
    [self.mGraphTimeTypeTableView setSeparatorColor:[UIHelp colorWithHexString:@"0xe0e0e0"]];
    self.mGraphTimeTypeTableView.dataSource = self;
    self.mGraphTimeTypeTableView.delegate = self;
    self.mGraphTimeTypeTableView.alpha = 0.0f;
    self.mGraphTimeTypeSelectionView.alpha = 0.0f;
    
    selectButtonType = false;
    
}

- (void)dealloc {

    [_mGraphTimeTypeSelectionView removeFromSuperview];
    [_mGraphTimeTypeTableView removeFromSuperview];
    [_mGraphTimeTypeSelectionView release];
    [_mGraphTimeTypeTableView release];
    [_lableTimeType release];
    [_lableTitle release];
    [_mSelectTypeButtonUp release];
    [_mSelectTypeButtonDown release];
    [_mGraphTimeDict release];
//    [_dataSource release];
    
    [super dealloc];
}
//showMessageTypeList函数用于点击button时显示table与隐藏
- (void)showMessageTypeList: (BOOL)show {
    if (show) {
        [self.mGraphTimeTypeTableView reloadData];
        
        //[UIView beginAnimations:@"pick" context:nil];
        //[UIView setAnimationDuration:0.4f]; 
        self.mGraphTimeTypeTableView.alpha = 1.0f;
        self.mGraphTimeTypeSelectionView.alpha = 0.5f;
        
        
        self.mSelectTypeButtonDown.hidden = YES;
        self.mSelectTypeButtonUp.hidden   = NO;
        selectButtonType = true;
        //[UIView commitAnimations];

        
        
    } else {
        //[self.mGraphTimeTypeTableView removeFromSuperview];
        //[self.mGraphTimeTypeSelectionView removeFromSuperview];
        //[UIView beginAnimations:@"pick" context:nil];
        //[UIView setAnimationDuration:0.3f]; 
        self.mGraphTimeTypeTableView.alpha = 0.0f;
        self.mGraphTimeTypeSelectionView.alpha = 0.0f;
        self.mSelectTypeButtonDown.hidden = NO;
        self.mSelectTypeButtonUp.hidden   = YES;
        selectButtonType = false;
        //[UIView commitAnimations];
        //[self.mGraphTimeTypeTableView reloadData];
    }
}

- (IBAction)onSelectMsgType: (id)sender {
    if (self.mSelectTypeButtonDown == sender) { 
        [self showMessageTypeList:YES];
    } else {
        [self showMessageTypeList:NO];
    }
}

#pragma table

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    return 44;
}

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{        
    // Message Type table view
    return self.mGraphTimeDict.count;
    //return 8;
    
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    NSInteger row = [indexPath row];
       
    if(self.mGraphTimeDict !=  nil && self.mGraphTimeDict.count > 0)
    {
        UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier: @"GraphPickViewCell"];
        if (cell == nil)  
        {
            cell = [[[UITableViewCell alloc]initWithStyle:UITableViewCellStyleDefault reuseIdentifier:@"GraphPickViewCell"] autorelease];
            
        }
        cell.accessoryType = (row == lastIndex) ? UITableViewCellAccessoryCheckmark :UITableViewCellAccessoryNone;
        cell.selectionStyle=UITableViewCellSelectionStyleGray; 
        //cell.accessoryType = (row == oldRow) ? UITableViewCellAccessoryCheckmark :UITableViewCellAccessoryNone;
        cell.textLabel.text = (NSString *)([self.mGraphTimeDict objectAtIndex:row]);
        cell.textLabel.textAlignment = UITextAlignmentCenter;
        
        NSLog(@"cell accessoryType : %d",cell.accessoryType);
        return cell;
    }
    return nil;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath { 
    NSUInteger row = [indexPath row];   
    
    if (row != lastIndex) {
        UITableViewCell *newCell = [tableView cellForRowAtIndexPath:indexPath];
        newCell.accessoryType = UITableViewCellAccessoryCheckmark;
        
        NSIndexPath * prevIndexPath = [NSIndexPath indexPathForRow:lastIndex inSection:0];
        UITableViewCell *oldCell = [tableView cellForRowAtIndexPath:prevIndexPath];
        oldCell.accessoryType = UITableViewCellAccessoryNone;
        self.lastIndex = [indexPath row];

    }
    self.mGraphFilter = row;
    //[self.mGraphTimeTypeTableView deselectRowAtIndexPath:indexPath animated:NO];
    [self showMessageTypeList:NO]; 
    self.lableTimeType.text = [NSString stringWithFormat:@"(%@)",[self.mGraphTimeDict objectAtIndex:row]];
    
    [self.dataSource pickView:self mSelectType:self.mGraphFilter];
    [self.mGraphTimeTypeTableView deselectRowAtIndexPath:indexPath animated:YES];
}

-(void) viewWillAppear:(BOOL)animated
{
    self.mGraphTimeTypeTableView.alpha = 0.0f;
    self.mGraphTimeTypeSelectionView.alpha = 0.0f;

    UIView *superView = [self.dataSource superView];
    self.mGraphTimeTypeSelectionView.frame = CGRectMake(0, 44, 480, 276);
    [self.dataSource addSubview: self.mGraphTimeTypeSelectionView];
    self.mGraphTimeTypeTableView.frame = CGRectMake(superView.center.x, 44 ,118,[self.mGraphTimeDict count] * 44 );
    //self.mGraphTimeTypeTableView.frame = CGRectMake(0, 44, 480, 276);
    NSLog(@"self.mGraphTimeTypeTableView.frame.size.width: %f",self.mGraphTimeTypeTableView.frame.size.width);
    [self.dataSource insertSubview:self.mGraphTimeTypeTableView aboveSubview:self.mGraphTimeTypeTableView];
    //当addSubview后需要将原来的子类view release掉，因为addSubview函数会将计数器加1

        
    
    
    
}
- (IBAction)myActionMethod:(id)sender
{
    [self onSelectMsgType: _mSelectTypeButtonUp];
}

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
    NSSet *allTouches = [event allTouches];
    
    switch ([allTouches count]) {
        case 1: {
            if (selectButtonType) {
                [self onSelectMsgType: _mSelectTypeButtonUp];
            }
            else {
                [self onSelectMsgType: _mSelectTypeButtonDown];
            }
        } break;
            
        case 2: {
            // potential zoom gesture
            
        } break;
            
        default:
            
            break;
            
    }
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
