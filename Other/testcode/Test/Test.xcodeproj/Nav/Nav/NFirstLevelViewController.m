//
//  NFirstLevelViewController.m
//  Nav
//
//  Created by 佳 刘 on 12-9-17.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "NFirstLevelViewController.h"
#import "NSecondLevelViewController.h"
#import "NDisclosureButtonController.h"
#import "NCheckListViewController.h"
#import "NRowControllsController.h"
#import "NMoveMeController.h"
#import "NDeleteMeController.h"
#import "NPresidentViewController.h"

@interface NFirstLevelViewController ()

@end

@implementation NFirstLevelViewController
@synthesize controllers;

- (id)initWithStyle:(UITableViewStyle)style
{
    self = [super initWithStyle:style];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];

    // Uncomment the following line to preserve selection between presentations.
    // self.clearsSelectionOnViewWillAppear = NO;
 
    // Uncomment the following line to display an Edit button in the navigation bar for this view controller.
    // self.navigationItem.rightBarButtonItem = self.editButtonItem;
    self.title = @"firstLevel";
    
    NSMutableArray *array = [[[NSMutableArray alloc]init]autorelease];
    NDisclosureButtonController *dcontroller = [[[NDisclosureButtonController alloc]initWithStyle:UITableViewStylePlain]autorelease];
    dcontroller.title = @"disclosure buttons";
    dcontroller.rowImg = [UIImage imageNamed:@"disclosureBUttonControllerIcon.png"];
    [array addObject:dcontroller];
    
    NCheckListViewController *checklistController = [[[NCheckListViewController alloc]initWithStyle:UITableViewStylePlain]autorelease];
    checklistController.title = @"check one";
    checklistController.rowImg = [UIImage imageNamed:@"checkmarkControllerIcon.png"];
    [array addObject:checklistController];
    
    NRowControllsController *rowController = [[[NRowControllsController alloc]initWithStyle:UITableViewStylePlain]autorelease];
    rowController.title = @"row controls";
    rowController.rowImg = [UIImage imageNamed:@"rowControlsIcon.png"];
    [array addObject:rowController];
    
    NMoveMeController *moveController = [[[NMoveMeController alloc]initWithStyle:UITableViewStylePlain]autorelease];
    moveController.title = @"move me";
    moveController.rowImg = [UIImage imageNamed:@"moveMeIcon.png"];
    [array addObject:moveController];
    
    NDeleteMeController *delController = [[[NDeleteMeController alloc]initWithStyle:UITableViewStylePlain]autorelease];
    delController.title = @"delete me";
    delController.rowImg = [UIImage imageNamed:@"deleteMeIcon.png"];
    [array addObject:delController];
    
    NPresidentViewController *presidentController = [[[NPresidentViewController alloc]initWithStyle:UITableViewStylePlain]autorelease];
    presidentController.title = @"presidents";
    presidentController.rowImg = [UIImage imageNamed:@"detailEditIcon.png"];
    [array addObject:presidentController];
    
    self.controllers = array;
}

- (void)viewDidUnload
{
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}

#pragma mark - Table view data source

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
    // Return the number of sections.
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    // Return the number of rows in the section.
    return [self.controllers count];
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    static NSString *CellIdentifier = @"Cell";
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
    
    // Configure the cell...
    if (cell == nil) {
        cell = [[[UITableViewCell alloc]initWithStyle:UITableViewCellStyleDefault reuseIdentifier:CellIdentifier]autorelease];
        
    }
    
    NSecondLevelViewController *controller = [self.controllers objectAtIndex:indexPath.row];
    
    cell.textLabel.text = controller.title;
    cell.imageView.image = controller.rowImg;
    cell.accessoryType = UITableViewCellAccessoryDetailDisclosureButton;
    
    return cell;
}

/*
// Override to support conditional editing of the table view.
- (BOOL)tableView:(UITableView *)tableView canEditRowAtIndexPath:(NSIndexPath *)indexPath
{
    // Return NO if you do not want the specified item to be editable.
    return YES;
}
*/

/*
// Override to support editing the table view.
- (void)tableView:(UITableView *)tableView commitEditingStyle:(UITableViewCellEditingStyle)editingStyle forRowAtIndexPath:(NSIndexPath *)indexPath
{
    if (editingStyle == UITableViewCellEditingStyleDelete) {
        // Delete the row from the data source
        [tableView deleteRowsAtIndexPaths:[NSArray arrayWithObject:indexPath] withRowAnimation:UITableViewRowAnimationFade];
    }   
    else if (editingStyle == UITableViewCellEditingStyleInsert) {
        // Create a new instance of the appropriate class, insert it into the array, and add a new row to the table view
    }   
}
*/

/*
// Override to support rearranging the table view.
- (void)tableView:(UITableView *)tableView moveRowAtIndexPath:(NSIndexPath *)fromIndexPath toIndexPath:(NSIndexPath *)toIndexPath
{
}
*/

/*
// Override to support conditional rearranging of the table view.
- (BOOL)tableView:(UITableView *)tableView canMoveRowAtIndexPath:(NSIndexPath *)indexPath
{
    // Return NO if you do not want the item to be re-orderable.
    return YES;
}
*/

#pragma mark - Table view delegate

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    // Navigation logic may go here. Create and push another view controller.
    /*
     <#DetailViewController#> *detailViewController = [[<#DetailViewController#> alloc] initWithNibName:@"<#Nib name#>" bundle:nil];
     // ...
     // Pass the selected object to the new view controller.
     [self.navigationController pushViewController:detailViewController animated:YES];
     [detailViewController release];
     */
    
    NSecondLevelViewController *second = [self.controllers objectAtIndex:indexPath.row];
    
    [self.navigationController pushViewController:second animated:YES];
}

@end
