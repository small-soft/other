//
//  searchPickerView.h
//  AlibabaMobile
//
//  Created by alimobile on 12-4-13.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
@class searchPickerView;
@protocol searchPickerViewDelegate <NSObject>

-(void)searchPickerView:(searchPickerView*)picker selected:(NSUInteger)selectedPicker;
@optional
-(void)searchPickerViewWillAppear:(searchPickerView*)picker;
@end
@interface searchPickerView : UIView <UITableViewDataSource,UITableViewDelegate>
{
    UIControl *myView;
}
@property (retain, nonatomic) IBOutlet UITableView *contentTable;
@property (nonatomic,retain)  IBOutlet UIControl   *myView;
@property (nonatomic,retain)  IBOutlet UIImageView *imageView;
#warning xiugairen 孟希羲
//@property (nonatomic,retain) NSObject <searchPickerViewDelegate> *delegate;
@property (nonatomic,assign) id <searchPickerViewDelegate> delegate;
+(id)createView;
-(IBAction)myClickAction:(id)sender;
@end
