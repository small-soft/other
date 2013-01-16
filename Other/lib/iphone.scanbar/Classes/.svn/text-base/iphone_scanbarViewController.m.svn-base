//
//  iphone_scanbarViewController.m
//  iphone.scanbar
//
//  Created by wangjun on 10-12-26.
//  Copyright __MyCompanyName__ 2010. All rights reserved.
//

#import "iphone_scanbarViewController.h"
@implementation iphone_scanbarViewController
@synthesize resultText,resultImage;
- (void)viewDidLoad {
    [super viewDidLoad];
}
- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
}
- (void)viewDidUnload {
	self.resultText=nil;
	self.resultImage=nil;
}
- (void)dealloc {
	[self.resultText release];
	[self.resultImage release];
    [super dealloc];
}
#pragma mark -
#pragma mark onClickButton
-(IBAction)onButton:(id)sender
{
    ZBarReaderViewController *reader = [ZBarReaderViewController new];
    reader.readerDelegate = self;
    ZBarImageScanner *scanner = reader.scanner;
    [scanner setSymbology: ZBAR_I25
				   config: ZBAR_CFG_ENABLE
					   to: 0];
    [self presentModalViewController: reader
							animated: YES];
    [reader release];
	
}
- (void) imagePickerController: (UIImagePickerController*) reader
 didFinishPickingMediaWithInfo: (NSDictionary*) info
{
    id<NSFastEnumeration> results =
	[info objectForKey: ZBarReaderControllerResults];
    ZBarSymbol *symbol = nil;
    for(symbol in results)
        break;
		NSLog(@"===%@",symbol.data);
    resultText.text = symbol.data;
    resultImage.image =
	[info objectForKey: UIImagePickerControllerOriginalImage];
    [reader dismissModalViewControllerAnimated: YES];
}

@end
