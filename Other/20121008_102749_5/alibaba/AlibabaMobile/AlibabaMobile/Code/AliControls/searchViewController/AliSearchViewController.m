//
//  AliSearchViewController.m
//  AlibabaMobile
//
//  Created by alimobile on 12-4-12.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AliSearchViewController.h"
#import "AMOfferListViewController.h"
#import "AMSearchCompanyViewController.h"
#import "AMSearchPriceViewController.h"
#import "searchViewDef.h"
@interface AliSearchViewController ()

@end

@implementation AliSearchViewController
@synthesize searchView=_searchView;

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
        self.navigationItem.title = @"搜索";
    }
    return self;
}

- (void)viewDidLoad
{
//    [self.navigationController setNavigationBarHidden:YES animated:YES];
    self.searchView.delegate = self;
    [self.searchView editBecomeFirstResponder];
    [super viewDidLoad];

	// Do any additional setup after loading the view.
}

- (void)viewDidUnload
{
    //[self setSearchView:nil];
    _searchView = nil;
    [super viewDidUnload];
    // Release any retained subviews of the main view.
}

-(void)viewWillAppear:(BOOL)animated
{
    [self.navigationController setNavigationBarHidden:YES animated:NO];
//    [self.navigationController setNavigationBarHidden:NO animated:NO];
}

-(void)viewWillDisappear:(BOOL)animated
{
    [self.navigationController setNavigationBarHidden:NO animated:YES];
}
- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}

- (void)dealloc {
    [_searchView release];
    [super dealloc];
}

//-(NSString*)commonTableViewNavigationTitle {
//    return @"搜索";
//}
//
//-(NSString*)commonTableViewBackButtonTitle {
//    return @"应用中心";
//}



-(void)searchBarEditViewEditBegin:(AliSearchView*)searchBarView
{
//     [self.navigationController setNavigationBarHidden:YES animated:YES];
 
}

-(void)searchBarEditViewDidEnd:(AliSearchView *)searchView content:(NSString *)content selected:(NSUInteger)selected
{
        switch (selected) {
        case SEARCH_COMPANY:
            {
            AMSearchCompanyViewController *Controller = [[AMSearchCompanyViewController alloc] initWithNibName:@"AMSearchCompanyViewController" bundle:nil];
            Controller.keyWords = content;
//            Controller.parentTitle = @"应用中心";
            Controller.parentTitle = @"搜索";
            Controller.hidesBottomBarWhenPushed=YES;   
                [self.navigationController pushViewController:Controller animated:YES];
                [Controller release];
            }
            break;
        case SEARCH_PRICE:
            {
            AMSearchPriceViewController *Controller = [[AMSearchPriceViewController alloc] initWithNibName:@"AMSearchPriceViewController" bundle:nil];
            Controller.keyWords=content;
            Controller.hidesBottomBarWhenPushed=YES;
//            Controller.parentTitle = @"应用中心";
            Controller.parentTitle = @"搜索";
            [self.navigationController pushViewController:Controller animated:YES];   
                [Controller release];
            }
            break;
        case SEARCH_PRODUCT:   
        default:
            {
            AMOfferListViewController *Controller = [[AMOfferListViewController alloc] initWithNibName:@"AMOfferListViewController" bundle:nil];
            Controller.keyWords = content;
//            Controller.parentTitle = @"应用中心";
            Controller.parentTitle = @"搜索";
            Controller.hidesBottomBarWhenPushed=YES;
                  [self.navigationController pushViewController:Controller animated:YES];
                [Controller release];
            }

            break;
    }
    
    // 将搜索框得内容置为和选择得关键词一致
    self.searchView.editView.editTextField.text = content;
    [self.navigationController setNavigationBarHidden:NO animated:YES];

}
-(void)searchBarEditCancel:(AliSearchView*)searchBarView
{
//    [self.navigationController popViewControllerAnimated:YES];
    
    [self.searchView resignFirstResponder];
    [self.searchView historyBecomeFirstResponder];
}

@end
