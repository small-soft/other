//
//  STViewController.m
//  SimpleTabel
//
//  Created by 佳 刘 on 12-9-10.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "STViewController.h"

@interface STViewController ()

@end

@implementation STViewController
@synthesize listData = _listData;


#pragma - mark
#pragma mark vc lifecycle
- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.
    self.listData = [NSArray arrayWithObjects:@"sleepy",@"sneezy",@"bashful",@"happy",@"doc",@"grumpy",@"dopey",@"thorin", nil];
}

- (void)viewDidUnload
{
    self.listData = nil;
    [super viewDidUnload];
    // Release any retained subviews of the main view.
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return (interfaceOrientation != UIInterfaceOrientationPortraitUpsideDown);
}

#pragma - mark
#pragma mark table view data source method
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return [self.listData count];
}

-(UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"simpleTableId"];
    if(cell == nil){
        cell = [[[UITableViewCell alloc]initWithStyle:UITableViewCellStyleValue2 reuseIdentifier:@"simpleTableId"]autorelease];
        
    }
    
    UIImage *image = [UIImage imageNamed:@"star.png"];
    cell.imageView.image = image;
    cell.imageView.highlightedImage = [UIImage imageNamed:@"star2.png"];
    
    cell.textLabel.text = [self.listData objectAtIndex:indexPath.row];
    
    cell.detailTextLabel.text = @"Mr hhaha";
    
    // 改变字体，大小
    cell.textLabel.font = [UIFont boldSystemFontOfSize:50];
    
    return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    
    UIAlertView *alert = [[[UIAlertView alloc]initWithTitle:[NSString stringWithFormat:@"you select %d row",indexPath.row] message:@"yeah!" delegate:nil cancelButtonTitle:@"ok" otherButtonTitles: nil]autorelease];
    
    [alert show];
    
    [tableView deselectRowAtIndexPath:indexPath animated:YES];
}

-(CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath {
    return 70;
}

@end
