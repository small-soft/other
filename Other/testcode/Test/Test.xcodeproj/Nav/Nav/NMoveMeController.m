//
//  NMoveMeController.m
//  Nav
//
//  Created by 佳 刘 on 12-9-18.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "NMoveMeController.h"

@interface NMoveMeController ()

@end

@implementation NMoveMeController
@synthesize list;

#pragma mark -
#pragma mark vc lifecycle
- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)viewDidLoad
{
    if (self.list == nil) {
        self.list = [NSMutableArray arrayWithObjects:@"eeny",@"meeny",@"miney",@"moe",@"catch", nil];
    }
    UIBarButtonItem *movebtn = [[[UIBarButtonItem alloc] initWithTitle:@"Move" style:UIBarButtonItemStyleBordered target:self action:@selector(toggleMove)]autorelease];
    
    self.navigationItem.rightBarButtonItem = movebtn;
    
    [super viewDidLoad];
	// Do any additional setup after loading the view.
}

- (void)viewDidUnload
{
    [self.list release];
    [super viewDidUnload];
    // Release any retained subviews of the main view.
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}

#pragma mark -
#pragma mark action
- (void)toggleMove {
[self.tableView setEditing:!self.tableView.editing animated:YES];
if(self.tableView.editing){
    [self.navigationItem.rightBarButtonItem setTitle:@"Done"];
}else {
    [self.navigationItem.rightBarButtonItem setTitle:@"Move"];
}
}

#pragma mark -
#pragma mark table view delegate
-(NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return [self.list count];
}

-(UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    static NSString *moveIdentifier = @"MoveMeCellIdentifier";
    
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:moveIdentifier];
    
    if (cell == nil) {
        cell = [[[UITableViewCell alloc]initWithStyle:UITableViewCellStyleDefault reuseIdentifier:moveIdentifier]autorelease];
        cell.showsReorderControl = YES;
    }
    
cell.textLabel.text = [list objectAtIndex:indexPath.row];

return cell;
}

- (UITableViewCellEditingStyle)tableView:(UITableView *)tableView editingStyleForRowAtIndexPath:(NSIndexPath *)indexPath {
    return UITableViewCellEditingStyleNone;
}

-(BOOL)tableView:(UITableView *)tableView canMoveRowAtIndexPath:(NSIndexPath *)indexPath {
    return YES;
}

-(void)tableView:(UITableView *)tableView moveRowAtIndexPath:(NSIndexPath *)sourceIndexPath toIndexPath:(NSIndexPath *)destinationIndexPath {
NSUInteger fromRow = sourceIndexPath.row;
NSUInteger toRow = destinationIndexPath.row;

id obj = [[[self.list objectAtIndex:fromRow]retain]autorelease];
[self.list removeObjectAtIndex:fromRow];
[self.list insertObject:obj atIndex:toRow];
}

@end
