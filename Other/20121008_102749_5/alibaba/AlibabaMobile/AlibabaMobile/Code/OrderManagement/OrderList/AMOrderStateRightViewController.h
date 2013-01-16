
#import <UIKit/UIKit.h>
#import "AliCommonTableView.h"



@interface AMOrderStateRightViewController : AliCommonTableView <UITableViewDelegate, UITableViewDataSource> {
    NSArray *tableTitles;
}

@property (nonatomic, retain) UIView *headerView;
@property (nonatomic, retain) IBOutlet UITableView *mTableView;
@property (nonatomic, retain) IBOutlet UITableView *orderStateTableView;
@property (nonatomic, retain) NSArray * sourceData;
@property (nonatomic)NSUInteger selectedItem;
- (void)setVisible:(BOOL)visible;

@end
