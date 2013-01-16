//
//  AMGroupCell.m
//  NAMenu
//
//  Created by  on 12-8-23.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMGroupCell.h"
#import "AMMenuItemView.h"
#import "AMGroupTableViewController.h"
#import "ConstDef.h"
#import "UIHelp.h"
@implementation AMGroupCell

@synthesize itemText = _itemText;
@synthesize parentTableController = _parentTableController;
@synthesize menuView = _menuView;
@synthesize subItemsCount = _subItemsCount;
@synthesize expandImage = _expandImage;
@synthesize expandBtn = _expandBtn;
@synthesize itemDescribeText = _itemDescribeText;
@synthesize bottomLine = _bottomLine;
//@synthesize isLoaded = _isLoaded;
- (id)init {
	self = [super init];
	
	if (self = [self initWithStyle:AMGroupCellStyleLeftButton]) {
        
	}
	
	return self;
}

-(id)initWithStyle:(AMGroupCellStyle)style{
    self = [super init];
	
	if (self) {
        switch (style) {
            case AMGroupCellStyleLeftButton:
            {
                NSArray *views = [[NSBundle mainBundle] loadNibNamed:@"AMGroupCellStyleLeftButton" owner:self options:nil];
           
                self = [[views objectAtIndex:0] retain];
                
                _menuView.menuDelegate =self;
                _menuView.topPadding = 10;
                _menuView.columnCount = 5;
                _menuView.yPadding = 10;
                _menuView.itemSize = CGSizeMake(57, 57);
                _menuView.leftPadding = 10;
                UIScreen * mainScreen = [UIScreen mainScreen];
                CGFloat scale = [mainScreen scale];
                if (scale==1) {
                    _bottomLine.frame = CGRectMake(0, self.frame.size.height-2, self.frame.size.width, 2);
                    _bottomLine.autoresizingMask = UIViewAutoresizingFlexibleTopMargin|UIViewAutoresizingFlexibleRightMargin;
                }
                _bottomLine.backgroundColor = [UIColor colorWithPatternImage:[UIImage imageNamed:@"c_line_2px.png"]];
                self.backgroundView.backgroundColor = [UIColor colorWithPatternImage:[UIImage imageNamed:@"c_first_bg.png"]];
//                self.backgroundView.layer.contents = (id)[UIImage imageNamed:@"c_first_bg.png"].CGImage;
                break;
            }
            case AMGroupCellStyleRightArrowButton:{
                NSArray *views = [[NSBundle mainBundle] loadNibNamed:@"AMGroupCellStyleRightArrowButton" owner:self options:nil];
                
                self = [[views objectAtIndex:0] retain];
                
                _menuView.menuDelegate =self;
                _menuView.topPadding = 0;
                _menuView.bottomPadding = 0;
                _menuView.columnCount = 3;
                _menuView.itemSize = CGSizeMake(108, 43);
                _menuView.layer.borderWidth = 0.5;
                _menuView.layer.borderColor = [[UIHelp colorWithHexString:@"0xe6e8e9"] CGColor];
                break;
            }
            default:
                break;
        }
        
	}
	
	return self;
}
-(void)awakeFromNib{
    _menuView.menuDelegate =self;
    _menuView.topPadding = 0;
    _menuView.columnCount = 4;
}
- (void) layoutSubviews
{
    [super layoutSubviews];
    [self setupInterface];
}

- (void) setupInterface
{
    [self setClipsToBounds: YES];
//    _expandBtn.frame = CGRectMake(0, 5, 40, 40);

    [_expandBtn addTarget:self.parentTableController action:@selector(collapsableButtonTapped:withEvent:) forControlEvents:UIControlEventTouchUpInside];

//    _expandBtn.alpha = 0.1;
}

#pragma mark - NAMenuViewDelegate Methods

- (NSInteger)menuViewNumberOfItems:(id)menuView {
    //	NSAssert([self menuItems], @"You must set menuItems before attempting to load.");
	return _subItemsCount;
}

- (AMMenuItemView *)menuView:(AMMenuView *)menuView inGroupCellIndexPath:(NSIndexPath *)indexPath ItemViewForRowAtIndex:(NSInteger)index{

    AMMenuItemView * itemView = [self.parentTableController inGroupCellIndexPath:indexPath subItemForRowAtIndex:index];
    return itemView;
}

- (void)menuView:(AMMenuView *)menuView didSelectItemAtIndex:(NSInteger)index {

	AMMenuItemView * itemView = [self menuView:menuView inGroupCellIndexPath:[((AMGroupTableViewController*)self.parentTableController).tableView indexPathForCell:self] ItemViewForRowAtIndex:index];
    [self.parentTableController groupCellIndexPath:[((AMGroupTableViewController*)self.parentTableController).tableView indexPathForCell:self] didSelectSubItem:itemView withIndex:index];
}

- (void)dealloc
{
    AM_RELEASE_SAFELY(_itemText);
//    AM_RELEASE_SAFELY(_parentTableController);
    AM_RELEASE_SAFELY(_menuView);
    AM_RELEASE_SAFELY(_expandBtn);
    AM_RELEASE_SAFELY(_expandImage);
    AM_RELEASE_SAFELY(_itemDescribeText);
    AM_RELEASE_SAFELY(_bottomLine);
    [super dealloc];
    
}
//为了让与之关联的button一起亮
-(void)setHighlighted:(BOOL)highlighted animated:(BOOL)animated{
    self.expandBtn.highlighted = highlighted;
    [super setHighlighted:highlighted animated: animated];
}

-(void)setSelected:(BOOL)selected animated:(BOOL)animated{
    self.expandBtn.selected = selected;
    [super setSelected:selected animated:animated];
}

-(void)menuView:(AMMenuView *)menuView ItemPressedAtIndex:(NSInteger)index{
    
}
-(void)menuView:(AMMenuView *)menuView ItemPressedDownAtIndex:(NSInteger)inde{
    
}
-(void)menuView:(AMMenuView *)menuView ItemPressedUpOutsideActionAtIndex:(NSInteger)index{
    
}

-(void) rotateExpandBtn:(BOOL)isExpand{

    if (isExpand) {
        [UIView beginAnimations:@"rotateDisclosureButt" context:nil];
        [UIView setAnimationDuration:0.2];
        self.expandBtn.transform = CGAffineTransformMakeRotation(M_PI);
        [UIView commitAnimations];
    }else {
        [UIView beginAnimations:@"rotateDisclosureButt" context:nil];
        [UIView setAnimationDuration:0.2];
        self.expandBtn.transform = CGAffineTransformMakeRotation(2*M_PI);
        [UIView commitAnimations];
    }
}

@end
