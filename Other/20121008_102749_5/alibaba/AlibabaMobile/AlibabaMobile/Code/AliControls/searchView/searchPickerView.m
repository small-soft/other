//
//  searchPickerView.m
//  AlibabaMobile
//
//  Created by alimobile on 12-4-13.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "searchPickerView.h"
#import "searchViewDef.h"
#import "AliTableViewCellPicker.h"
@interface searchPickerView()

@property (nonatomic,retain) NSMutableArray *contentData;

@end
@implementation searchPickerView
@synthesize contentTable=_contentTable;
@synthesize contentData=_contentData;
@synthesize delegate = _delegate;
@synthesize myView;
@synthesize imageView = _imageView;
-(void)dealloc
{

    [_contentTable release];
    [_contentData release];
    [_imageView release];
#warning mengxixi
    //[_delegate release];
    [myView release];
    [super dealloc];
}


-(NSMutableArray*)contentData
{
    if (!_contentData) {
        _contentData = [[NSArray arrayWithObjects:
                        [NSDictionary dictionaryWithObjectsAndKeys:@"产 品",@"title",@"search_price.png",@"icon", nil],
                         [NSDictionary dictionaryWithObjectsAndKeys:@"公 司",@"title", @"search_company.png",@"icon",nil],
                         [NSDictionary dictionaryWithObjectsAndKeys:@"价 格",@"title", @"search_product.png",@"icon",nil],
                        nil] retain];
    }
    return _contentData;
}

-(void)setupView
{
    self.contentTable.frame = CGRectMake(10.0, 4.5, [AliTableViewCellPicker cellWidth], [AliTableViewCellPicker cellHeight]*[self.contentData count]);
    [self.contentTable.layer setCornerRadius:10.0];
    self.imageView.frame = CGRectMake(7.0, 0.5, self.contentTable.frame.size.width + 8, self.contentTable.frame.size.height + 8);
//    self.myView.frame = 
    self.myView.backgroundColor = [UIColor blackColor]; 
//    NSLog(@"self.frame.size.width : %f",self.frame.size.width);
    UIImage *image = [UIImage imageNamed:@"search_picker_bg"];
    image = [ image stretchableImageWithLeftCapWidth: image.size.width/2 topCapHeight: image.size.height/2 ];
//    self.imageView.image = image;
    CGSize itemSize = self.imageView.frame.size;
    UIGraphicsBeginImageContext(itemSize);
    CGRect imageRect = CGRectMake(0.0, 0.0, itemSize.width, itemSize.height);
    //[imageTmp drawInRect:imageRect];
    [image drawInRect:imageRect];
    self.imageView.image = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();


    //self.myView.alpha = 0.0f;

}

-(IBAction)myClickAction:(id)sender
{
    self.hidden = YES;
    if ([self.delegate respondsToSelector:@selector(searchPickerViewWillAppear:)]) {
        [self.delegate searchPickerViewWillAppear:self];
    }
}

+(id)createView
{
    NSArray *nib = [[NSBundle mainBundle] loadNibNamed:@"searchPickerView" 
                                                 owner:self options:nil];
    for (id oneObject in nib)
    {
        if ([oneObject isKindOfClass:[searchPickerView class]])
        {
            searchPickerView *obj = (searchPickerView *)oneObject;
            [obj setupView];
//            [obj.contentTable selectRowAtIndexPath:[NSIndexPath indexPathForRow:0 inSection:0] animated:NO scrollPosition:0];
  
            return  obj;
        }
    }
    return nil;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return [self.contentData count];
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    return [AliTableViewCellPicker cellHeight];;
}

-(UITableViewCell*)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    AliTableViewCellPicker *cell = (AliTableViewCellPicker *)[tableView 
                                                                            dequeueReusableCellWithIdentifier: [AliTableViewCellPicker cellIdentifer]];
    if (cell == nil)  
    {
        cell = [AliTableViewCellPicker createCell];
    
    }
    NSUInteger row = [indexPath row];
    NSDictionary *data = [self.contentData objectAtIndex:row]; 
    cell.icon.image = [UIImage imageNamed:[data objectForKey:@"icon"]];
    
    cell.title.text = [data objectForKey:@"title"];
    
    return cell;
}
- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
     NSUInteger row = [indexPath row];
    if ([self.delegate respondsToSelector:@selector(searchPickerView:selected:)]) {
        [self.delegate searchPickerView:self selected:row];
    }
    [tableView deselectRowAtIndexPath:indexPath animated:YES];

}


@end
