//
//  searchPickerView.m
//  AlibabaMobile
//
//  Created by alimobile on 12-6-28.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AliTableViewMyCustomerPickerView.h"
//#import "searchViewDef.h"
#import "AliTableViewMyCustomerCellPicker.h"
@interface AliTableViewMyCustomerPickerView()

@end
@implementation AliTableViewMyCustomerPickerView
@synthesize contentTable=_contentTable;
@synthesize contentData=_contentData;
@synthesize delegatePicker = _delegatePicker;
@synthesize buttonPressType = _buttonPressType;

-(void)dealloc
{
    [_contentTable release];
    [_contentData release];
    [_delegatePicker release];
    [super dealloc];
}

- (id)initWithGroupArray:(NSMutableArray *)array
{
    [super initWithFrame:CGRectMake(10.0, 100.0, [AliTableViewMyCustomerCellPicker cellWidth], [AliTableViewMyCustomerCellPicker cellHeight]*[array count]) style:UITableViewStylePlain];
    if (self) {
        self.delegate  = self;
        self.dataSource = self;
        self.contentData = array;
        [self.contentTable reloadData];
        self.bounces = NO;
        self.scrollEnabled = YES;
        [self.contentTable selectRowAtIndexPath:[NSIndexPath indexPathForRow:0 inSection:0] animated:NO scrollPosition:0];
    }
    return self;
}



- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return [self.contentData count];
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    return [AliTableViewMyCustomerCellPicker cellHeight];;
}

-(UITableViewCell*)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    AliTableViewMyCustomerCellPicker *cell = (AliTableViewMyCustomerCellPicker *)[tableView 
                                                                            dequeueReusableCellWithIdentifier: [AliTableViewMyCustomerCellPicker cellIdentifer]];
    if (cell == nil)  
    {
        cell = [AliTableViewMyCustomerCellPicker createCell];
    
    }
    NSUInteger row = [indexPath row];
    NSString *title = [self.contentData objectAtIndex:row];
    cell.title.text = title;
    
    return cell;
}
- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
     NSUInteger row = [indexPath row];
     NSString *content = [self.contentData objectAtIndex:row];
     NSUInteger type = self.buttonPressType;
    if ([self.delegatePicker respondsToSelector:@selector(pickerView:selected:content:type:)]) {
        [self.delegatePicker pickerView:self selected:row content:content type:type];
    }

//    switch (self.buttonPressType) {
//        case 0:
//        {
//            if ([self.delegatePicker respondsToSelector:@selector(categoryPickerView:selected:content:)]) {
//                [self.delegatePicker categoryPickerView:self selected:row content:content];
//            }
//        }
//            break;
//        case 1:
//        {
//            if ([self.delegatePicker respondsToSelector:@selector(areaPickerView:selected:content:)]) {
//                [self.delegatePicker areaPickerView:self selected:row content:content];
//            }
//        }    
//        default:
//            break;
//    }
    
}


@end
