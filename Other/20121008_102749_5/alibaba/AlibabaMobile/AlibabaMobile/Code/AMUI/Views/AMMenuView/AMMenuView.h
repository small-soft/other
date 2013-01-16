
@class AMMenuView,AMMenuItemView;
@protocol AMMenuViewDelegate <NSObject>
@required
- (NSInteger)menuViewNumberOfItems:(AMMenuView *)menuView;

- (void)menuView:(AMMenuView *)menuView didSelectItemAtIndex:(NSInteger)index;

@optional
- (AMMenuItemView *)menuView:(AMMenuView *)menuView ItemViewForRowAtIndex:(NSInteger)index;
//only used for groupcelltableviewcontroller
- (AMMenuItemView *)menuView:(AMMenuView *)menuView inGroupCellIndexPath:(NSIndexPath*)indexPath ItemViewForRowAtIndex:(NSInteger)index;

//用于不规则的itemsize 现阶段只支持itemsize宽度不同 高度相同也许有问题。。大家可以试试。。。并且一定注意暂时不支持groupcell内的乱七八糟这种。
- (CGSize)menuView:(AMMenuView*)menuView ItemSizeForRowAtIndex:(NSInteger)index;

//用于用户点击后响应，如更改背景图片，背景颜色等
- (void)menuView:(AMMenuView*)menuView  ItemPressedDownAtIndex:(NSInteger)index;
- (void)menuView:(AMMenuView*)menuView  ItemPressedAtIndex:(NSInteger)index;
- (void)menuView:(AMMenuView*)menuView  ItemPressedUpOutsideActionAtIndex:(NSInteger)index;
- (void)menuView:(AMMenuView*)menuView  ItemPressedCancelActionAtIndex:(NSInteger)index;
@end

@interface AMMenuView : UIScrollView

@property (nonatomic, assign) id<AMMenuViewDelegate>menuDelegate;
@property (nonatomic, retain) UIImageView * backgroundImageView;
/**
 * You can use these properties if you would like a different number of columns or
 * different-sized menu items.
 */
@property (nonatomic) NSUInteger columnCount;// default is 4
@property (nonatomic) CGSize itemSize; // default is 80*90.
@property (nonatomic) NSInteger topPadding;
@property (nonatomic) NSInteger leftPadding;
@property (nonatomic) NSInteger bottomPadding;
//其中Ypadding必须大于-1 如果等于-1则说明没有设定。
@property (nonatomic) NSInteger yPadding;
-(void)reloadData;
//only used for groupcelltableviewcontroller
-(void)reloadDataWithGroupCellIndexPath:(NSIndexPath*)indexPath;
//只用于不规则大小布局的显示。
@property (nonatomic) NSUInteger autoSizeMAXRow ;//default is 2
@end
