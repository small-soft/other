//
//  CViewController.m
//  Cells
//
//  Created by 佳 刘 on 12-9-10.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "CViewController.h"
#import "CCell.h"

@interface CViewController ()

@end

@implementation CViewController
@synthesize computers = _computers;

#pragma - mark
#pragma mark vc lifecycle
- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.
    NSDictionary *d1 = [NSDictionary dictionaryWithObjectsAndKeys:@"mackbook",@"name",@"white",@"color", nil];
    NSDictionary *d2 = [NSDictionary dictionaryWithObjectsAndKeys:@"mackbook pro",@"name",@"silver",@"color" ,nil];
    NSDictionary *d3 = [NSDictionary dictionaryWithObjectsAndKeys:@"imac",@"name",@"white",@"color", nil];
    NSDictionary *d4 = [NSDictionary dictionaryWithObjectsAndKeys:@"mac ini",@"name",@"white",@"color", nil];
    NSDictionary *d5 = [NSDictionary dictionaryWithObjectsAndKeys:@"mac pro",@"name",@"silver",@"color" ,nil];
    
    self.computers = [NSArray arrayWithObjects:d1,d2,d3,d4,d5, nil];
}

- (void)viewDidUnload
{
    self.computers = nil;
    [super viewDidUnload];
    // Release any retained subviews of the main view.
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return (interfaceOrientation != UIInterfaceOrientationPortraitUpsideDown);
}

#pragma - mark
#pragma mark table view data source
-(NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return [self.computers count];
}

-(UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    
//    UITableViewCell *cell = [self defaultCellForTableView:tableView atIndexPath:indexPath];
    UITableViewCell *cell = [self customCellForTableView:tableView atIndexPath:indexPath];
    return cell;
}

-(CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath {
    return 132.;
}
#pragma - mark
#pragma mark some method
- (UITableViewCell *) defaultCellForTableView:(UITableView *)tableView atIndexPath:(NSIndexPath *)indexPath {
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"cells"];
    
    if (cell == nil) {
        cell = [[[UITableViewCell alloc]initWithStyle:UITableViewCellStyleDefault reuseIdentifier:@"cells"]autorelease];
        
        UILabel *nameLabel = [[[UILabel alloc]initWithFrame:CGRectMake(0, 5, 70, 15)]autorelease];
        nameLabel.text = @"Name";
        [cell.contentView addSubview:nameLabel];
        
        UILabel *nameValueLabel = [[[UILabel alloc]initWithFrame:CGRectMake(80, 5, 200, 15)]autorelease];
        nameValueLabel.text = [[[self.computers objectAtIndex:indexPath.row] objectForKey:@"name"]autorelease];
        nameValueLabel.tag = kNameValueTag;
        [cell.contentView addSubview:nameValueLabel];
        
        UILabel *colorLabel = [[[UILabel alloc]initWithFrame:CGRectMake(0, 26, 70, 15)]autorelease];
        colorLabel.text = @"Color";
        [cell.contentView addSubview:colorLabel];
        
        UILabel *colorValueLabel = [[[UILabel alloc]initWithFrame:CGRectMake(80, 25, 200, 15)]autorelease];
        colorValueLabel.text = [[[self.computers objectAtIndex:indexPath.row] objectForKey:@"color"]autorelease];
        colorValueLabel.tag = kColorValueTag;
        [cell.contentView addSubview:colorValueLabel];
    }
    
    NSString *name = [[[self.computers objectAtIndex:indexPath.row] objectForKey:@"name"]autorelease];
    
    NSString *color = [[[self.computers objectAtIndex:indexPath.row] objectForKey:@"color"]autorelease];
    
    UILabel *nameLabel = (UILabel *)[cell.contentView viewWithTag:kNameValueTag];
    nameLabel.text = name;
    UILabel *colorLabel = (UILabel *)[cell.contentView viewWithTag:kColorValueTag];
    colorLabel.text = color;
    
    return cell;
}

- (UITableViewCell *) customCellForTableView:(UITableView *)tableView atIndexPath:(NSIndexPath *)indexPath {
    CCell *cell = [tableView dequeueReusableCellWithIdentifier:@"ccells"];
    
    if (cell == nil) {
        NSArray *nib = [[NSBundle mainBundle] loadNibNamed:@"CCell" owner:self options:nil];
        for (id oneObject in nib) {
            if ([oneObject isKindOfClass:[CCell class]]) {
                cell = (CCell *)oneObject;
            }
        }

    }
    
    cell.name.text = [[[self.computers objectAtIndex:indexPath.row] objectForKey:@"name"]autorelease];
    
    cell.color.text = [[[self.computers objectAtIndex:indexPath.row] objectForKey:@"color"]autorelease];

    
    return cell;
}

@end
