//
//  NPresidentViewController.m
//  Nav
//
//  Created by 佳 刘 on 12-9-20.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "NPresidentViewController.h"
#import "NPresident.h"
#import "NPresidentDetailController.h"

@interface NPresidentViewController ()
@property (nonatomic,retain) NSMutableArray *list;

@end

@implementation NPresidentViewController
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
    NSString *path = [[NSBundle mainBundle]pathForResource:@"Presidents" ofType:@"plist"];
    NSData *data = [[[NSData alloc]initWithContentsOfFile:path]autorelease];
    NSKeyedUnarchiver *unarchiver = [[[NSKeyedUnarchiver alloc]initForReadingWithData:data]autorelease];
    
    NSMutableArray *array = [unarchiver decodeObjectForKey:@"Presidents"];
    self.list = array;
    [unarchiver finishDecoding];
    
    
    [super viewDidLoad];
	// Do any additional setup after loading the view.
}

-(void) viewWillAppear:(BOOL)animated {
    [self.tableView reloadData];
    [super viewWillAppear:animated];
}

- (void)viewDidUnload
{
    self.list = nil;
    [super viewDidUnload];
    // Release any retained subviews of the main view.
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}

#pragma mark -
#pragma mark table view delegate & datasource
-(NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return [self.list count];
}

-(UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    static NSString *identifier = @"presidentIdentifier";
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:identifier];
    
    if (cell == nil) {
        cell = [[UITableViewCell alloc]initWithStyle:UITableViewCellStyleSubtitle reuseIdentifier:identifier];
    }
    
    President *p = [self.list objectAtIndex:indexPath.row];
    cell.textLabel.text = p.name;
    cell.detailTextLabel.text = [NSString stringWithFormat:@"%@ - %@",p.fromYear,p.toYear];
    return cell;
}

-(void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    NPresidentDetailController *detail = [[[NPresidentDetailController alloc]initWithStyle:UITableViewStylePlain]autorelease];
    detail.president = [self.list objectAtIndex:indexPath.row];
    
    [self.navigationController pushViewController:detail animated:YES];
}

@end
