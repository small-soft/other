//
//  AMSubpageWithMenuViewController.m
//  AlibabaMobile
//
//  Created by  on 12-8-28.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AMSubpageWithMenuViewController.h"
#import "AMGroupCell.h"
#import "AMSubpageTreeResult.h"
#import "AMSubpageRecommendOrHistoryResult.h"

#import "AMMenuView.h"
#import "AMMenuItemView.h"
#import "ConstDef.h"
#import "AMSubpageResult.h"
#import "AMOfferListViewController.h"
#import "UIHelp.h"
@implementation AMSubpageWithMenuViewController

@synthesize recommendOrHistoryData = _recommendOrHistoryData;


-(NSMutableArray *)recommendOrHistoryData{
    if (!_recommendOrHistoryData) {
        _recommendOrHistoryData = [[NSMutableArray alloc] init];
    }
    return _recommendOrHistoryData;
}

#pragma mark - 主table的事件 请实现

-(void)mainTable:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath{

    
    AMSubpageTreeChildren *subpageTreeChildren = ((AMSubpageTreeChildren*)[self.subpageChildrenData objectAtIndex:[indexPath row]]);
    
    if (!subpageTreeChildren.hasChild) {
        [AMLogUtils appendLog:APP_OTHERINDUSTRY_BROWSER_THREE];
        AMOfferListViewController *controller = [[AMOfferListViewController alloc] initWithNibName:@"AMOfferListViewController" bundle:nil];
        if ([subpageTreeChildren.type isEqualToString:@"keyword"]) {
            controller.keyWords = subpageTreeChildren.name;
        }

        controller.catId = subpageTreeChildren.ID;
        controller.catName = subpageTreeChildren.name;
        controller.parentCatId = subpageTreeChildren.ID;
        controller.navigationCategoryId = self.subpageRequest.categoryId;
        controller.parentTitle = self.navigationItem.title;


        controller.hidesBottomBarWhenPushed=YES;
        [self.navigationController pushViewController:controller animated:YES];
        [controller release];
    }else {
            
//        NSIndexPath * preIndexPath = self.expandedIndexPath.copy; 
            
        
        if ([indexPath isEqual: self.expandedIndexPath]) {
            self.expandedIndexPath = nil;
        }else {
            [AMLogUtils appendLog:APP_OTHERINDUSTRY_BROWSER_THREE];
            if (self.expandedIndexPath) {
                self.expandedIndexPath = indexPath;
            }else {
                self.expandedIndexPath = indexPath;
            }
        }

        [self.tableView reloadData];
        CATransition *animation = [CATransition animation];
        [animation setType:kCATransitionReveal];
        [animation setSubtype:kCATransitionFromBottom];
        [animation setTimingFunction:[CAMediaTimingFunction functionWithName:kCAMediaTimingFunctionLinear]];
        [animation setFillMode:kCAFillModeBoth];
        [animation setDuration:0.8];
        [[((AMGroupCell*)[self.tableView cellForRowAtIndexPath:indexPath]).menuView layer] addAnimation:animation forKey:@"UITableViewReloadDataAnimationKey"];

//        if ([indexPath isEqual:preIndexPath]) {
//            [self rotateExpandBtn:NO withIndexPath:indexPath];
//        }else {
//            if (preIndexPath) {
//                [self rotateExpandBtn:NO withIndexPath:preIndexPath];
//                [self rotateExpandBtn:YES withIndexPath:indexPath];
//            }else {
//                [self rotateExpandBtn:YES withIndexPath:indexPath];
//            }
//        }
        
        [tableView scrollToRowAtIndexPath:indexPath atScrollPosition:UITableViewScrollPositionTop animated:YES];
    }


}

- (CGFloat) tableView:(UITableView *)tableView heightForGroupCellBackGroundViewAtIndexPath:(NSIndexPath *)indexPath{
    return 43;
}

//想要不同效果覆盖此方法
- (AMGroupCell *) mainTable:(UITableView *)mainTable itemForRowAtIndexPath:(NSIndexPath *)indexPath{
    AMGroupCell *cell = [[[AMGroupCell alloc] initWithStyle:AMGroupCellStyleRightArrowButton] autorelease] ;
    
    return cell;
}

-(AMGroupCell *)mainTable:(UITableView *)mainTable setItem:(AMGroupCell *)cell forRowAtIndexPath:(NSIndexPath *)indexPath{
    AMSubpageTreeChildren *subpageTreeChildren = ((AMSubpageTreeChildren*)[self.subpageChildrenData objectAtIndex:[indexPath row]]);
    cell.itemText.text = subpageTreeChildren.name;
    cell.backgroundView.layer.borderWidth=0.5;   
    cell.backgroundView.layer.borderColor=[[UIHelp colorWithHexString:@"0xe6e8e9"] CGColor];
    if(!subpageTreeChildren.hasChild){
        cell.expandBtn.hidden = YES;
    }else {
        cell.expandBtn.hidden = NO;
    }
    //    cell.expandImage.url = [NSURL URLWithString:subpageTreeChildren.imageUrl];
    //[self.objMan manage:cell.expandImage];
    return cell;
}

#pragma mark - 下拉的menuView的方法 请实现

//想要不同效果覆盖此方法
- (AMMenuItemView *) inGroupCellIndexPath:(NSIndexPath*)groupCellIndexPath subItemForRowAtIndex:(NSInteger)index{
    AMMenuItemView *itemView = [[[AMMenuItemView alloc]initWithStyle:AMMenuItemViewStyleTextOnly] autorelease];
    
    AMSubpageTreeChildren *subpageChilden = ((AMSubpageTreeChildren*)[self.subpageChildrenData objectAtIndex:[groupCellIndexPath row]]);
    if (subpageChilden.hasChild) {
        itemView.label.text = ((AMSubpageTreeChildren*)[subpageChilden.children objectAtIndex:index]).name;
    }
    itemView.layer.borderWidth=1;   
    itemView.layer.borderColor=[[UIHelp colorWithHexString:@"0xe6e8e9"] CGColor]; 
    if ([subpageChilden.type isEqualToString:@"event"]) {
        itemView.leftTopTagImageView.image = [UIImage imageNamed:@"category_hot.png"];
    }
    itemView.backgroundColor = [UIHelp colorWithHexString:@"0xffffff"];
    return itemView;
}

#pragma mark view life cycle 

-(void)viewDidLoad{

    _recommendOrHistoryMenuView.menuDelegate = self;
    _recommendOrHistoryMenuView.bottomPadding = 5;
    self.navigationItem.title = self.categoryName;
    [super viewDidLoad];
}

-(void)viewDidUnload{
    [super viewDidUnload];
    self.recommendOrHistoryData = nil;
    _recommendOrHistoryMenuView = nil;
    _recommendOrHistoryMenuViewTitle = nil;
}

-(void)dealloc{
    AM_RELEASE_SAFELY(_recommendOrHistoryMenuView);
    AM_RELEASE_SAFELY(_recommendOrHistoryMenuViewTitle);
    AM_RELEASE_SAFELY(_recommendOrHistoryData);
    [super dealloc];
}

- (id) init
{
    if (self = [self initWithNibName:@"AMSubpageWithMenuView" bundle:nil])
    {
        self.tableView.layer.borderWidth = 0.5;
        self.tableView.layer.borderColor = [[UIHelp colorWithHexString:@"0xe6e8e9"] CGColor];
    }
    return self;
}

#pragma mark menuView delegate
- (NSInteger)menuViewNumberOfItems:(AMMenuView *)menuView{
    return [self.recommendOrHistoryData count];
}

- (void)menuView:(AMMenuView *)menuView didSelectItemAtIndex:(NSInteger)index{
    if ([_recommendOrHistoryMenuViewTitle.text isEqualToString:@"热门推荐"]) {
        [AMLogUtils appendLog:APP_OTHERINDUSTRY_BROWSER_ONE];
    }else if ([_recommendOrHistoryMenuViewTitle.text isEqualToString:@"浏览历史"]) {
        [AMLogUtils appendLog:APP_OTHERINDUSTRY_BROWSER_TWO];
    }
    
    AMSubpageRecommendOrHistoryChildren *subpageRecommendOrHistoryChildren = (AMSubpageRecommendOrHistoryChildren*)[self.recommendOrHistoryData objectAtIndex:index];
    AMOfferListViewController *controller = [[AMOfferListViewController alloc] initWithNibName:@"AMOfferListViewController" bundle:nil];
    if ([subpageRecommendOrHistoryChildren.type isEqualToString:@"keyword"]) {
        controller.keyWords = subpageRecommendOrHistoryChildren.name;
    }
    controller.catId = subpageRecommendOrHistoryChildren.ID;
    controller.catName = subpageRecommendOrHistoryChildren.name;
    controller.parentTitle = self.navigationItem.title;
    controller.parentCatId= subpageRecommendOrHistoryChildren.ID;
    //    controller.categoryFilterSelectedItem = index;
    controller.navigationCategoryId = self.subpageRequest.categoryId;
    controller.hidesBottomBarWhenPushed=YES;
    [self.navigationController pushViewController:controller animated:YES];
    [controller release];
}

- (AMMenuItemView *)menuView:(AMMenuView *)menuView ItemViewForRowAtIndex:(NSInteger)index{
    AMMenuItemView *itemView = [[[AMMenuItemView alloc]initWithStyle:AMMenuItemViewStyleTextOnly] autorelease];
    AMSubpageRecommendOrHistoryChildren *subpageRecommendOrHistoryChildren = (AMSubpageRecommendOrHistoryChildren*)[self.recommendOrHistoryData objectAtIndex:index];
    itemView.label.text = subpageRecommendOrHistoryChildren.name;
    UIImage * backgroundImage = [UIImage imageNamed:@"category_tag.png"];
    itemView.imageViewBackground.image = [backgroundImage stretchableImageWithLeftCapWidth:backgroundImage.size.width/2 topCapHeight:backgroundImage.size.height/2];
    return itemView;
}

- (CGSize)menuView:(AMMenuView*)menuView ItemSizeForRowAtIndex:(NSInteger)index{
    AMSubpageRecommendOrHistoryChildren *subpageRecommendOrHistoryChildren = (AMSubpageRecommendOrHistoryChildren*)[self.recommendOrHistoryData objectAtIndex:index];
    CGSize labelSize = [subpageRecommendOrHistoryChildren.name sizeWithFont:[UIFont fontWithName:@"Heiti TC" size:18] constrainedToSize:CGSizeMake(300, 460) lineBreakMode:UILineBreakModeCharacterWrap];
    labelSize.height = 40;
    return labelSize;
}

//- (void)objectLoader:(RKObjectLoader*)objectLoader didFailWithError:(NSError*)error{
//    
//}
- (void)objectLoader:(RKObjectLoader*)objectLoader didLoadObjects:(NSMutableArray*)objects 
{
    if ([objectLoader.params respondsToSelector:@selector(transactionType)]) {
        NSInteger transactionType = [(NSObject<AMRequestDelegate> *)objectLoader.params transactionType];
        
        if(transactionType == AMTRANSACTION_TYPE_SUBPAGE_REQUEST){
            AMSubpageResult * result = (AMSubpageResult*) [objects objectAtIndex:0];
            if (result.history.hasChild) {
                [self.recommendOrHistoryData removeAllObjects];
                [self.recommendOrHistoryData addObjectsFromArray:result.history.children];
                [_recommendOrHistoryMenuView reloadData];
                _recommendOrHistoryMenuViewTitle.text = @"浏览历史";
                _recommendOrHistoryMenuView.frame = CGRectMake(0, _recommendOrHistoryMenuViewTitle.frame.size.height+_recommendOrHistoryMenuViewTitle.frame.origin.y, _recommendOrHistoryMenuView.contentSize.width, _recommendOrHistoryMenuView.contentSize.height);
                self.tableView.frame = CGRectMake(0,_recommendOrHistoryMenuViewTitle.frame.size.height + _recommendOrHistoryMenuView.contentSize.height+_recommendOrHistoryMenuViewTitle.frame.origin.y , self.view.frame.size.width, self.view.frame.size.height - (_recommendOrHistoryMenuViewTitle.frame.size.height + _recommendOrHistoryMenuView.contentSize.height+_recommendOrHistoryMenuViewTitle.frame.origin.y ));
                
            }else if(result.recommend.hasChild) {
                [self.recommendOrHistoryData removeAllObjects];
                [self.recommendOrHistoryData addObjectsFromArray:result.recommend.children];
                [_recommendOrHistoryMenuView reloadData];
                _recommendOrHistoryMenuViewTitle.text = @"热门推荐";
                _recommendOrHistoryMenuView.frame = CGRectMake(0, _recommendOrHistoryMenuViewTitle.frame.size.height+_recommendOrHistoryMenuViewTitle.frame.origin.y, _recommendOrHistoryMenuView.contentSize.width, _recommendOrHistoryMenuView.contentSize.height);
                self.tableView.frame = CGRectMake(0,_recommendOrHistoryMenuViewTitle.bounds.size.height + _recommendOrHistoryMenuView.contentSize.height+_recommendOrHistoryMenuViewTitle.frame.origin.y , self.view.frame.size.width, self.view.frame.size.height - (_recommendOrHistoryMenuViewTitle.frame.size.height + _recommendOrHistoryMenuView.contentSize.height+_recommendOrHistoryMenuViewTitle.frame.origin.y ));
            }else {
                self.tableView.frame = CGRectMake(0, 0, self.view.frame.size.width, self.view.frame.size.height);
            }
        }
    }
    [super objectLoader:objectLoader didLoadObjects:objects];

}

@end
