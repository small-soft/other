//
//  NRowControllsController.m
//  Nav
//
//  Created by 佳 刘 on 12-9-18.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "NRowControllsController.h"

@interface NRowControllsController ()

@end

@implementation NRowControllsController
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
    self.list = [NSArray arrayWithObjects:@"r2-d2",@"c3p0",@"tik-tok",@"robby",@"tobor", nil];
    
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
-(void)buttonTapped:(id)sender {
    // 如果获取btn所在的cell
    UIButton *btn = (UIButton *)sender;
    UITableViewCell *buttonCell = (UITableViewCell *)[btn superview];
    
    NSUInteger btnRow = [[self.tableView indexPathForCell:buttonCell] row];
    NSString *btnTitle = [self.list objectAtIndex:btnRow];
//    NSString *btnTitle = buttonCell.textLabel.text;
    [self alertForTitle:btnTitle];
    
}

-(void)alertForTitle:(NSString *)title {
    UIAlertView *alert = [[[UIAlertView alloc]initWithTitle:@"you tapped the button" message:[NSString stringWithFormat:@"you tapped the button for %@",title] delegate:nil cancelButtonTitle:@"ok" otherButtonTitles: nil]autorelease];
    [alert show];
}

#pragma mark -
#pragma mark table view delegate & datasource
-(NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return [self.list count];
}

-(UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    static NSString *controllerRowId = @"controllerRowId";
    
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:controllerRowId];
    
    if (cell == nil) {
        cell = [[[UITableViewCell alloc]initWithStyle:UITableViewCellStyleDefault reuseIdentifier:controllerRowId]autorelease];
        UIImage *buttonUpImage = [UIImage imageNamed:@"button_up.png"];
        UIImage *buttonDownImage = [UIImage imageNamed:@"button_down.png"];
        UIButton *btn = [UIButton buttonWithType:UIButtonTypeCustom];
        btn.frame = CGRectMake(0., 0., buttonUpImage.size.width, buttonUpImage.size.height);
        [btn setBackgroundImage:buttonUpImage forState:UIControlStateNormal];
        [btn setBackgroundImage:buttonDownImage forState:UIControlStateHighlighted];
        [btn setTitle:@"tab" forState:UIControlStateNormal];
        
//        btn.titleLabel.text = @"tap";
        [btn addTarget:self action:@selector(buttonTapped:) forControlEvents:UIControlEventTouchUpInside];
        cell.accessoryView = btn;
    }

    cell.textLabel.text = [self.list objectAtIndex:indexPath.row];
    return cell;
}

-(void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    NSString *title = [tableView cellForRowAtIndexPath:indexPath].textLabel.text;
    
    [self alertForTitle:title];
}

@end
