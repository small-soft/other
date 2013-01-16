//
//  AMSubpageDressViewController.m
//  AlibabaMobile
//
//  Created by  on 12-8-27.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMSubpageDressViewController.h"
#import "UIHelp.h"
#import "ConstDef.h"
#import "AMSubpageResult.h"
#import "AMSubpageRequest.h"
#import "ConstDef.h"
#import "AMMenuItemView.h"
#import "AMGroupCell.h"
#import "AMToastView.h"
#import "AliNavigationBackButton.h"
#import "AMLogUtils.h"
#import "AMLogTypeCode.h"
@implementation AMSubpageDressViewController

#pragma mark - 主table的事件 请实现

- (void) mainTable:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath{
//    AMGroupCell *cell = (AMGroupCell*)[tableView cellForRowAtIndexPath:indexPath];
//    
//    [UIView setAnimationsEnabled:NO];
//    [UIView animateWithDuration:1 animations:^{ 
//        
//        if ([indexPath isEqual: self.expandedIndexPath]) {
//            self.expandedIndexPath = nil;
//        }else {
//            [AMLogUtils appendLog:APP_DRESSCATEGORY_BROWSER_ONE];
//            if (self.expandedIndexPath) {
//                self.expandedIndexPath = indexPath;
//
//            }else {
//                self.expandedIndexPath = indexPath;
//
//            }
//        }
//        [self.tableView reloadData];
//    }];
    
//    [UIView setAnimationsEnabled:YES];
    
    NSIndexPath * preIndexPath = self.expandedIndexPath.copy; 
    
    //    [self.tableView beginUpdates];
    if ([indexPath isEqual: self.expandedIndexPath]) {
        self.expandedIndexPath = nil;
        [self.tableView reloadRowsAtIndexPaths:[NSArray arrayWithObject:indexPath] withRowAnimation:UITableViewRowAnimationNone];
    }else {
        [AMLogUtils appendLog:APP_DRESSCATEGORY_BROWSER_ONE];
        if (self.expandedIndexPath) {
            self.expandedIndexPath = indexPath;
            [self.tableView reloadRowsAtIndexPaths:[NSArray arrayWithObjects:indexPath,preIndexPath,nil] withRowAnimation:UITableViewRowAnimationNone];
        }else {
            self.expandedIndexPath = indexPath;
            [self.tableView reloadRowsAtIndexPaths:[NSArray arrayWithObject:indexPath] withRowAnimation:UITableViewRowAnimationNone];
        }
    }
    [tableView scrollToRowAtIndexPath:indexPath atScrollPosition:UITableViewScrollPositionBottom animated:YES];
    
}
- (CGFloat) tableView:(UITableView *)tableView heightForGroupCellBackGroundViewAtIndexPath:(NSIndexPath *)indexPath{
    return 85;
}

- (AMGroupCell *) mainTable:(UITableView *)mainTable itemForRowAtIndexPath:(NSIndexPath *)indexPath{
    AMGroupCell *cell = [[[AMGroupCell alloc] initWithStyle:AMGroupCellStyleLeftButton] autorelease] ;

    return cell;
}

-(AMGroupCell *)mainTable:(UITableView *)mainTable setItem:(AMGroupCell *)cell forRowAtIndexPath:(NSIndexPath *)indexPath{
    AMSubpageTreeChildren *subpageTreeChildren = ((AMSubpageTreeChildren*)[self.subpageChildrenData objectAtIndex:[indexPath row]]);
    cell.itemText.text = subpageTreeChildren.name;
    [cell.expandImage clear];
    cell.expandImage.url = [NSURL URLWithString:subpageTreeChildren.imageUrl];
    [self.objMan manage:cell.expandImage];
//    cell.menuView.topPadding = 20;
//    cell.itemDescribeText.text = subpageTreeChildren.description; 
    cell.menuView.backgroundImageView.image = [[UIImage imageNamed:@"c_second_bg.png"] stretchableImageWithLeftCapWidth:56 topCapHeight:10];
    NSMutableString * descriptionString = [[NSMutableString alloc] init];
    for (AMSubpageTreeChildren* children in subpageTreeChildren.children) {
        [descriptionString appendString:children.name];
        if ([subpageTreeChildren.children indexOfObject:children]!=[subpageTreeChildren.children count]) {
            [descriptionString appendString:@" / "];
        }
    }
    cell.itemDescribeText.text = descriptionString;
    [descriptionString release];
//    cell.menuView.backgroundColor = [UIColor colorWithPatternImage:backgroundImage];
    return cell;
}

#pragma mark - 下拉的menuView的方法 请实现
//想要不同效果覆盖此方法
- (AMMenuItemView *) inGroupCellIndexPath:(NSIndexPath*)groupCellIndexPath subItemForRowAtIndex:(NSInteger)index{
    AMMenuItemView *itemView = [[[AMMenuItemView alloc]initWithStyle:AMMenuItemViewStyleImageAndText] autorelease];
    [itemView setLabelyPadding:-3 xPadding:0];
    itemView.label.font = [UIFont fontWithName:@"Heiti SC" size:11];
    itemView.label.textColor = [UIHelp colorWithHexString:@"0x666666"];
    AMSubpageTreeChildren *subpageChilden = ((AMSubpageTreeChildren*)[self.subpageChildrenData objectAtIndex:[groupCellIndexPath row]]);
    if (subpageChilden.hasChild) {
        itemView.label.text = ((AMSubpageTreeChildren*)[subpageChilden.children objectAtIndex:index]).name;
    }
    itemView.imageView.url = [NSURL URLWithString:((AMSubpageTreeChildren*)[subpageChilden.children objectAtIndex:index]).imageUrl];
    [self.objMan manage:itemView.imageView];
    itemView.imageViewBackground.image = [[UIImage imageNamed:@"c_second_pic_bg.png"] stretchableImageWithLeftCapWidth:5 topCapHeight:5];

    return itemView;
}

#pragma mark view life cycle 

-(void)viewDidLoad{

    //由于table初始化height的操作较生成cell早，因此当第一次为展开时就会存在bug，因此必须给一个初始化的参数 否则高度显示会有问题，这个是table的时机问题 暂时只能这么处理。
//    _menuViewTopPadding = 20;
//    _menuViewBottomPadding = 10;
    [super viewDidLoad];

}

-(id)init{
    if (self = [super init]) {
        _isFirstLoad = YES;
        self.subpageRequest.industryId = @"fuzhuangfushi";
        self.subpageRequest.categoryId = @"categories";
        self.navigationItem.title = @"服装服饰";
    }
    return self;
}

-(void)dealloc{

    [super dealloc];
}

//- (void)objectLoader:(RKObjectLoader*)objectLoader didFailWithError:(NSError*)error{
//    
//}
- (void)objectLoader:(RKObjectLoader*)objectLoader didLoadObjects:(NSMutableArray*)objects 
{
    [super objectLoader:objectLoader didLoadObjects:objects];
    if ([objectLoader.params respondsToSelector:@selector(transactionType)]) {
        NSInteger transactionType = [(NSObject<AMRequestDelegate> *)objectLoader.params transactionType];
        if(transactionType == AMTRANSACTION_TYPE_SUBPAGE_REQUEST){
            AMSubpageResult * result = (AMSubpageResult*) [objects objectAtIndex:0];
            if (result.tree.hasChild) {
                if (_isFirstLoad) {
                    //自动展开
                    
                    for (AMSubpageTreeChildren *chilren in result.tree.children ) {
                        if ([chilren.name isEqualToString:self.categoryName]) {
                           
                            
                            NSIndexPath * homeIndexPath = [NSIndexPath indexPathForRow:[result.tree.children indexOfObject:chilren] inSection:0];
                            [self performSelector:@selector(explandRowForIndexPath:) withObject:homeIndexPath afterDelay:0.05];

                            break;
                        }
                    }

                    
                    
                    _isFirstLoad = NO;
                }
            }
        }
    }
}

-(void)explandRowForIndexPath:(NSIndexPath*)indexPath{
    [self mainTable:self.tableView didSelectRowAtIndexPath:indexPath];
    [self.tableView scrollToRowAtIndexPath:indexPath atScrollPosition:UITableViewScrollPositionBottom animated:YES];
}
@end
