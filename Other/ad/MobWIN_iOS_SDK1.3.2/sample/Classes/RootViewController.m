//
//  RootViewController.m
//  MobWinSample
//
//  Created by Guo Zhao on 11-12-26.
//  Copyright 2011 Tencent. All rights reserved.
//

#import "RootViewController.h"
#import "AdViewController.h"
//#import "SpotViewController.h"

@implementation RootViewController


#pragma mark -
#pragma mark View lifecycle

- (void)viewDidLoad {
    [super viewDidLoad];

    // Uncomment the following line to display an Edit button in the navigation bar for this view controller.
	self.navigationItem.title = @"腾讯MobWIN v1.3.1";
	ads_iPhone = [[NSArray alloc] initWithObjects:@"320*50 广告条", @"320*25 广告条", /*@"插播 广告条", */nil];
	ads_iPad = [[NSArray alloc] initWithObjects:@"300*250 广告条", @"468*60 广告条", @"728*90 广告条", /*@"插播 广告条", */nil];
}

 // Override to allow orientations other than the default portrait orientation.
- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
	// Return YES for supported orientations.
	return YES;
}


#pragma mark -
#pragma mark Table view data source

// Customize the number of sections in the table view.
- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return 1;
}


// Customize the number of rows in the table view.
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
	if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
		return [ads_iPhone count];
 	} else {
		return [ads_iPad count];
	}
}


// Customize the appearance of table view cells.
- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    
    static NSString *CellIdentifier = @"Cell";
    
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
    if (cell == nil) {
        cell = [[[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:CellIdentifier] autorelease];
    }
	if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
		cell.textLabel.text = [ads_iPhone objectAtIndex:indexPath.row];
	} else {
		cell.textLabel.text = [ads_iPad objectAtIndex:indexPath.row];
	}

    return cell;
}


#pragma mark -
#pragma mark Table view delegate

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
	AdViewController *adVC = nil;
	if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
        // 如需植入MobWIN插播广告，请直接联系客户，谢谢！
		if (indexPath.row == 2 /*MobWinSpotView*/) {
			/*SpotViewController *spotVC = [[SpotViewController alloc] initWithNibName:@"SpotViewController_iPhone" bundle:nil];
			[self.navigationController pushViewController:spotVC animated:YES];
			[spotVC release];*/
		} else {
			adVC = [[AdViewController alloc] initWithNibName:@"AdViewController_iPhone" bundle:nil];
            switch (indexPath.row) {
                case 0:
					adVC.adType = MobWINBannerSizeIdentifier320x50;
					break;
				case 1:
					adVC.adType = MobWINBannerSizeIdentifier320x25;
					break;
            }
			[self.navigationController pushViewController:adVC animated:YES];
			[adVC release];
		}
	} else {
        // 如需植入MobWIN插播广告，请直接联系客户，谢谢！
		if (indexPath.row == 3) {
			/*SpotViewController *spotVC = [[SpotViewController alloc] initWithNibName:@"SpotViewController_iPad" bundle:nil];
			[self.navigationController pushViewController:spotVC animated:YES];
			[spotVC release];*/
		} else {
			adVC = [[AdViewController alloc] initWithNibName:@"AdViewController_iPad" bundle:nil];
			switch (indexPath.row) {
				case 0:
					adVC.adType = MobWINBannerSizeIdentifier300x250;
					break;
				case 1:
					adVC.adType = MobWINBannerSizeIdentifier468x60;
					break;
				case 2:
					adVC.adType = MobWINBannerSizeIdentifier728x90;
					break;
				default:
					break;
			}
			[self.navigationController pushViewController:adVC animated:YES];
			[adVC release];
		}
	}
}


#pragma mark -
#pragma mark Memory management

- (void)didReceiveMemoryWarning {
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Relinquish ownership any cached data, images, etc that aren't in use.
}

- (void)viewDidUnload {
    // Relinquish ownership of anything that can be recreated in viewDidLoad or on demand.
    // For example: self.myOutlet = nil;
}


- (void)dealloc {
	[ads_iPad release];
	[ads_iPhone release];
    [super dealloc];
}


@end

