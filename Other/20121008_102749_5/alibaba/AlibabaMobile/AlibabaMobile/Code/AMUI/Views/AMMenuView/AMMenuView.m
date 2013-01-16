
#import "AMMenuView.h"
#import "AMMenuItemView.h"
#import "ConstDef.h"
#import "UIHelp.h"
#define AUTOITEMSIZEPADDING 10.0
@interface AMMenuView()
@property (nonatomic, retain) UIColor *itemBackgroundColor;
@property (nonatomic, retain) NSMutableArray *itemViews;
- (void)setupItemViews;
- (void)itemPressed:(id)sender;
@end

@implementation AMMenuView
@synthesize itemBackgroundColor = _itemBackgroundColor;
@synthesize menuDelegate = _menuDelegate;
@synthesize backgroundImageView = _backgroundImageView;
@synthesize itemViews = _itemViews;
@synthesize columnCount = _columnCount;
@synthesize itemSize = _itemSize;
@synthesize topPadding = _topPadding;
@synthesize leftPadding = _leftPadding;
@synthesize bottomPadding = _bottomPadding;
@synthesize yPadding = _yPadding;
@synthesize autoSizeMAXRow = _autoSizeRow;
#pragma mark - Memory Management

- (id)init {
	self = [super init];
	
	if (self) {
		_itemViews = [[NSMutableArray alloc] init];
		_backgroundImageView = [[UIImageView alloc]init];
		// set some defaults
		_columnCount = 4;
		_itemSize = CGSizeMake(80, 80);
        _yPadding = -1;
        _autoSizeRow = 2;
	}
	
	return self;
}

-(id)initWithCoder:(NSCoder *)aDecoder{
	
	if (self = [super initWithCoder:aDecoder]) {
		_itemViews = [[NSMutableArray alloc] init];
		_backgroundImageView = [[UIImageView alloc]init];
		// set some defaults
		_columnCount = 4;
		_itemSize = CGSizeMake(80, 80);
        _yPadding = -1;
        _autoSizeRow = 2;
	}
	
	return self;
}
- (void)dealloc {
    AM_RELEASE_SAFELY(_menuDelegate);
    AM_RELEASE_SAFELY(_itemViews);
    AM_RELEASE_SAFELY(_backgroundImageView);
    AM_RELEASE_SAFELY(_itemBackgroundColor);
	[super dealloc];
}


#pragma mark - View Lifecycle

- (void)layoutSubviews {
	[super layoutSubviews];
}


#pragma mark - Local Methods

- (void)setupItemViews {
	
    NSUInteger numColumns = self.columnCount;
	
	NSUInteger numItems = [self.menuDelegate menuViewNumberOfItems:self];
    
    for (UIView *view in self.itemViews) {
		[view removeFromSuperview];
	}
	
	[self.itemViews removeAllObjects];
	
	// now add the new objects
    
    if ([self.menuDelegate respondsToSelector:@selector(menuView:ItemSizeForRowAtIndex:)]) {
        for (NSUInteger i = 0; i < numItems; i++) {
            
            AMMenuItemView * itemView = [self.menuDelegate menuView:self                                         ItemViewForRowAtIndex:i];
            
            itemView.frame = CGRectMake(0, 0, [self.menuDelegate menuView:self ItemSizeForRowAtIndex:i].width, [self.menuDelegate menuView:self ItemSizeForRowAtIndex:i].height);
            itemView.hidden = YES;
            itemView.tag = i;
            [itemView addTarget:self action:@selector(itemPressed:) forControlEvents:UIControlEventTouchUpInside];
            [itemView addTarget:self action:@selector(itemPressedDown:) forControlEvents:UIControlEventTouchDown];
            [itemView addTarget:self action:@selector(itemPressedUpOutsideAction:) forControlEvents:UIControlEventTouchUpOutside];
             [itemView addTarget:self action:@selector(itemPressedUpOutsideAction:) forControlEvents:UIControlEventTouchCancel];
            
            [self.itemViews addObject:itemView];
            [self addSubview:itemView];
        }
        
        CGFloat padding = AUTOITEMSIZEPADDING;
        CGFloat yPadding = AUTOITEMSIZEPADDING;
//        CGFloat totalHeight = ((self.itemSize.height + padding) * numRows) + padding;
        CGFloat totalHeight = yPadding;
        CGFloat columnWidth = padding + self.leftPadding;
        // get an even y padding if less than the max number of rows
        CGFloat maxHeight = 0;
        NSUInteger row = 0;
        for (int i = 0; i < numItems; i++) {
            UIView *item = [self.itemViews objectAtIndex:i];
            CGSize itemSize = item.bounds.size;
            if (maxHeight < itemSize.height ){
                maxHeight = itemSize.height;
            }
            CGFloat xOffset = 0;
            CGFloat yOffset = 0;
            if (columnWidth + itemSize.width + padding +self.leftPadding< self.bounds.size.width) {
                xOffset = columnWidth;
                yOffset = totalHeight;
                columnWidth += itemSize.width + padding;
                //若最后一次不需要换行则不加

            }else {
                row ++;
                if (row>=self.autoSizeMAXRow) {
                    break;
                }
                columnWidth = padding +self.leftPadding;
                totalHeight += maxHeight + yPadding;
                //保证最后一次使用的maxHeight还有值。
                if (i!=numItems-1) {
                    maxHeight = 0;
                }
                xOffset = columnWidth;
                yOffset = totalHeight;
                columnWidth += itemSize.width + padding;
            }
            item.frame = CGRectMake(xOffset, yOffset + self.topPadding, itemSize.width, itemSize.height);
            item.hidden = NO;

        }
        totalHeight += maxHeight + yPadding;
        //self.contentSize = CGSizeMake(self.bounds.size.width, totalHeight + self.topPadding + self.bottomPadding);
    }else{
        for (NSUInteger i = 0; i < numItems; i++) {
            
            AMMenuItemView * itemView = [self.menuDelegate menuView:self                                         ItemViewForRowAtIndex:i];
            
            itemView.frame = CGRectMake(0, 0, self.itemSize.width, self.itemSize.height);
            itemView.tag = i;
            [itemView addTarget:self action:@selector(itemPressed:) forControlEvents:UIControlEventTouchUpInside];
            [itemView addTarget:self action:@selector(itemPressedDown:) forControlEvents:UIControlEventTouchDown];
            [itemView addTarget:self action:@selector(itemPressedUpOutsideAction:) forControlEvents:UIControlEventTouchUpOutside];
             [itemView addTarget:self action:@selector(itemPressedUpOutsideAction:) forControlEvents:UIControlEventTouchCancel];
            
            [self.itemViews addObject:itemView];
            [self addSubview:itemView];
        }
        
        CGFloat padding = roundf((self.bounds.size.width - self.leftPadding*2-(self.itemSize.width * numColumns)) / (numColumns + 1));
//        NSUInteger numRows = numItems % numColumns == 0 ? (numItems / numColumns) : (numItems / numColumns) + 1;
//        CGFloat totalHeight = ((self.itemSize.height + padding) * numRows) + padding;
        
        // get an even y padding if less than the max number of rows
        CGFloat yPadding = padding;
        if (self.yPadding >= 0 ) {
            yPadding = self.yPadding;
        }
        
        for (int i = 0; i < numItems; i++) {
            UIView *item = [self.itemViews objectAtIndex:i];
            NSUInteger column = i % numColumns;
            NSUInteger row = i / numColumns;
            
            CGFloat xOffset = (column * (self.itemSize.width + padding)) + padding+self.leftPadding;
            CGFloat yOffset = (row * (self.itemSize.height + yPadding)) + yPadding;
            item.frame = CGRectMake(xOffset, yOffset + self.topPadding, self.itemSize.width, self.itemSize.height);
        }

//        self.contentSize = CGSizeMake(self.bounds.size.width, totalHeight + self.topPadding +self.bottomPadding);
    }
}

- (void)itemPressed:(UIButton *)sender {
	NSParameterAssert(sender);
    [self.menuDelegate menuView:self didSelectItemAtIndex:sender.tag];
    AMMenuItemView *view = (AMMenuItemView *)[sender superview];
    if ([self.menuDelegate respondsToSelector:@selector(menuView:ItemPressedAtIndex:)]) {
        [self.menuDelegate menuView:self ItemPressedAtIndex:sender.tag];
    }
    else {
        view.backgroundColor = self.itemBackgroundColor; 
    }
    
}

- (void)itemPressedDown:(UIButton *)sender {
    NSParameterAssert(sender);
    AMMenuItemView *view = (AMMenuItemView *)[sender superview];
    if ([self.menuDelegate respondsToSelector:@selector(menuView:ItemPressedDownAtIndex:)]) {
        [self.menuDelegate menuView:self ItemPressedDownAtIndex:sender.tag];
    }
    else {
        self.itemBackgroundColor = view.backgroundColor;
        view.backgroundColor = [UIHelp colorWithHexString:@"0xF2F2F2"];
    }
    
}

- (void)itemPressedUpOutsideAction:(UIButton *)sender {
    NSParameterAssert(sender);
    AMMenuItemView *view = (AMMenuItemView *)[sender superview];
    if ([self.menuDelegate respondsToSelector:@selector(menuView:ItemPressedUpOutsideActionAtIndex:)]) {
        [self.menuDelegate menuView:self ItemPressedUpOutsideActionAtIndex:sender.tag];
    }
    else {
        view.backgroundColor = self.itemBackgroundColor; 
    }
    
}


-(void)reloadData{
    [self setupItemViews];
    [self setupBackgroundImageView];
}

-(void)reloadDataWithGroupCellIndexPath:(NSIndexPath *)indexPath{
    [self setupItemViewsWithGroupCellIndexPath:indexPath];
    [self setupBackgroundImageView];
}

-(void)setupItemViewsWithGroupCellIndexPath:(NSIndexPath*)indexPath{
    NSUInteger numColumns = self.columnCount;
	
	NSUInteger numItems = [self.menuDelegate menuViewNumberOfItems:self];
    
    for (UIView *view in self.itemViews) {
		[view removeFromSuperview];
	}
	
	[self.itemViews removeAllObjects];
	
	// now add the new objects

    for (NSUInteger i = 0; i < numItems; i++) {
        
        AMMenuItemView * itemView = [self.menuDelegate menuView:self                                          inGroupCellIndexPath:indexPath ItemViewForRowAtIndex:i];
        
        itemView.frame = CGRectMake(0, 0, self.itemSize.width, self.itemSize.height);
        itemView.tag = i;
        [itemView addTarget:self action:@selector(itemPressed:) forControlEvents:UIControlEventTouchUpInside];
        [itemView addTarget:self action:@selector(itemPressedDown:) forControlEvents:UIControlEventTouchDown];
        [itemView addTarget:self action:@selector(itemPressedUpOutsideAction:) forControlEvents:UIControlEventTouchUpOutside];
        [itemView addTarget:self action:@selector(itemPressedUpOutsideAction:) forControlEvents:UIControlEventTouchCancel];
        
        [self.itemViews addObject:itemView];
        [self addSubview:itemView];
    }
    
    CGFloat padding = roundf((self.bounds.size.width-self.leftPadding*2 - (self.itemSize.width * numColumns)) / (numColumns + 1));
//    NSUInteger numRows = numItems % numColumns == 0 ? (numItems / numColumns) : (numItems / numColumns) + 1;
//    CGFloat totalHeight = ((self.itemSize.height + padding) * numRows) + padding;
    
    // get an even y padding if less than the max number of rows
    CGFloat yPadding = padding;
    if (self.yPadding>=0) {
        yPadding = self.yPadding;
    }

    for (int i = 0; i < numItems; i++) {
        UIView *item = [self.itemViews objectAtIndex:i];
        NSUInteger column = i % numColumns;
        NSUInteger row = i / numColumns;
        
        CGFloat xOffset = (column * (self.itemSize.width + padding)) + padding+self.leftPadding;
        CGFloat yOffset = (row * (self.itemSize.height + yPadding)) + yPadding;
        item.frame = CGRectMake(xOffset, yOffset + self.topPadding, self.itemSize.width, self.itemSize.height);
    }
    
//    self.contentSize = CGSizeMake(self.bounds.size.width, totalHeight + self.topPadding +self.bottomPadding);

}

-(void)setupBackgroundImageView{
    [self.backgroundImageView removeFromSuperview];
    if ([self.itemViews count] != 0) {
        [self insertSubview:self.backgroundImageView belowSubview:[self.itemViews objectAtIndex:0]];
    }else {
        [self addSubview:self.backgroundImageView];
    }
//    UIImage * backgroundImage = [UIImage imageNamed:@"submenuView_bg.png"] ;
//    [backgroundImage stretchableImageWithLeftCapWidth:10 topCapHeight:10];
//    self.backgroundImageView.image = backgroundImage;
    self.backgroundImageView.contentMode = UIViewContentModeScaleToFill;
    self.backgroundImageView.frame = CGRectMake(0, 0, self.contentSize.width, self.contentSize.height);

}
//自适应的大小
-(CGSize)contentSize{
    
    NSUInteger numColumns = self.columnCount;
	
	NSUInteger numItems = [self.menuDelegate menuViewNumberOfItems:self];
    
    if ([self.menuDelegate respondsToSelector:@selector(menuView:ItemSizeForRowAtIndex:)]) {
        
        CGFloat padding = AUTOITEMSIZEPADDING;
        CGFloat yPadding = AUTOITEMSIZEPADDING;

        CGFloat totalHeight = yPadding;
        CGFloat columnWidth = padding + self.leftPadding;
        // get an even y padding if less than the max number of rows
        CGFloat maxHeight = 0;
        NSUInteger row = 0;
        for (int i = 0; i < numItems; i++) {

            UIView *item = [self.itemViews objectAtIndex:i];
            CGSize itemSize = item.bounds.size;
            if (maxHeight < itemSize.height ){
                maxHeight = itemSize.height;
            }

            if (columnWidth + itemSize.width + padding + self.leftPadding< self.bounds.size.width) {

                columnWidth += itemSize.width + padding;

            }else {
                row ++;
                if (row>=self.autoSizeMAXRow) {
                    break;
                }
                columnWidth = padding +self.leftPadding;
                totalHeight += maxHeight + yPadding;
                //保证最后一次使用的maxHeight还有值。
                if (i!=numItems-1) {
                    maxHeight = 0;
                }

                columnWidth += itemSize.width + padding;
            }
        }
        totalHeight += maxHeight + yPadding;
        return CGSizeMake(self.bounds.size.width, totalHeight + self.topPadding + self.bottomPadding);
    }else {
        CGFloat padding = roundf((self.bounds.size.width - self.leftPadding*2 - (self.itemSize.width * numColumns)) / (numColumns + 1));
        NSUInteger numRows = numItems % numColumns == 0 ? (numItems / numColumns) : (numItems / numColumns) + 1;
        CGFloat yPadding = padding;
        if (self.yPadding>=0) {
            yPadding = self.yPadding;
        }
        CGFloat totalHeight = ((self.itemSize.height + yPadding) * numRows) + yPadding;
        
        // get an even y padding if less than the max number of rows

        return CGSizeMake(self.bounds.size.width, totalHeight + self.topPadding +self.bottomPadding);
    }
}
@end
