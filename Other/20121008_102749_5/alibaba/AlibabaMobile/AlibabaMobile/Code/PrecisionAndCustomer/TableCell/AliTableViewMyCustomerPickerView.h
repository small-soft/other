//
//  searchPickerView.h
//  AlibabaMobile
//
//  Created by alimobile on 12-6-28.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
@class AliTableViewMyCustomerPickerView;
@protocol AliTableViewMyCustomerPickerViewDelegate <NSObject>

//-(void)categoryPickerView:(AliTableViewMyCustomerPickerView*)picker selected:(NSUInteger)selectedPicker content:(NSString*)content;
//-(void)areaPickerView:(AliTableViewMyCustomerPickerView*)picker selected:(NSUInteger)selectedPicker content:(NSString*)content;
-(void)pickerView:(AliTableViewMyCustomerPickerView*)picker selected:(NSUInteger)selectedPicker content:(NSString*)content type:(NSUInteger)type;
@end
@interface AliTableViewMyCustomerPickerView : UITableView <UITableViewDataSource,UITableViewDelegate>{
    NSInteger buttonPressType;
}
@property (retain, nonatomic) IBOutlet UITableView *contentTable;
@property (nonatomic,retain) NSObject <AliTableViewMyCustomerPickerViewDelegate> *delegatePicker;
@property (nonatomic,retain) NSMutableArray *contentData;
@property (nonatomic, assign) NSInteger buttonPressType;
- (id)initWithGroupArray:(NSMutableArray *)array;
@end
