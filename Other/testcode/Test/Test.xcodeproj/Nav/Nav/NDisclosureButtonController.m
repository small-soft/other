//
//  NDisclosureButtonControllerViewController.m
//  Nav
//
//  Created by 佳 刘 on 12-9-18.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "NDisclosureButtonController.h"

@interface NDisclosureButtonController ()

@end

@implementation NDisclosureButtonController
@synthesize list;

#pragma - mark
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
    self.list = [NSArray arrayWithObjects:@"Toy stroy",@"a bug s life",@"monsters inc.",@"finding nemo",@"the incredibles",@"cars",@"newt" ,nil];
    [super viewDidLoad];
	// Do any additional setup after loading the view.
}

- (void)viewDidUnload
{
    self.list = nil;
    [childController release];
    childController = nil;
    [super viewDidUnload];
    // Release any retained subviews of the main view.
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}

#pragma - mark
#pragma mark table view delegate & datasource
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return [self.list count];
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    static NSString * identifier = @"DisclosureButtonCellIdetifier";
    
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:identifier];
    
    if (cell == nil) {
        cell = [[[UITableViewCell alloc]initWithStyle:UITableViewCellStyleDefault reuseIdentifier:identifier]autorelease];
        
    }
    
    cell.textLabel.text = [self.list objectAtIndex:indexPath.row];
    
    cell.accessoryType = UITableViewCellAccessoryDetailDisclosureButton;
    
    return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    UIAlertView *alert = [[[UIAlertView alloc]initWithTitle:@"Hey, do you see the disclosure button?" message:@"if you are trying to drill down ,touch that instead" delegate:nil cancelButtonTitle:@"won't hatten again" otherButtonTitles:nil]autorelease];
    
    [alert show];
}

-(void)tableView:(UITableView *)tableView accessoryButtonTappedForRowWithIndexPath:(NSIndexPath *)indexPath {
    if (childController == nil) {
        childController = [[[NDisclosureDetailController alloc]init]autorelease];
    }
    
    childController.title = @"disclosure button pressed";
    
    childController.message = [NSString stringWithFormat:@"you pressed the disclosure button for %@",[list objectAtIndex:indexPath.row]];
    
    childController.title = [list objectAtIndex:indexPath.row];
    
    [self.navigationController pushViewController:childController animated:YES];
}
@end
