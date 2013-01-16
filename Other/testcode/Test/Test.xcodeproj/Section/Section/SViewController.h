//
//  SViewController.h
//  Section
//
//  Created by 佳 刘 on 12-9-12.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface SViewController : UIViewController <UITableViewDelegate,UITableViewDataSource,UISearchBarDelegate> {
    NSDictionary *names;
    NSArray *keys;
    NSMutableArray *searchResult;
    UITableView *table;
    UISearchBar *search;
}

@property (retain,nonatomic) NSDictionary *names;
@property (retain,nonatomic) NSArray *keys;
@property (retain,nonatomic) NSMutableArray *searchResult;
@property (retain,nonatomic) IBOutlet UITableView *table;
@property (retain,nonatomic) IBOutlet UISearchBar *search;

@end
