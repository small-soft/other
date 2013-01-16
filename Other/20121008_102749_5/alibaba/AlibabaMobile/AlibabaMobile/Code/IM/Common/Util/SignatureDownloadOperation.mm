//
//  SignatureDownloadOperation.m
//  WangWang
//
//  Created by Casten on 10-7-5.
//  Copyright 2010 Infothinker. All rights reserved.
//

#import "SignatureDownloadOperation.h"
#import "CallBackTool.h"

@implementation SignatureDownloadOperation

- (id) initWithUID:(NSString *)_uid :(uint )_count{
	self = [super init];
	if (self != nil && _uid != nil) {
		uid = [[NSString alloc] initWithString:_uid];
        count =_count;
		[self setQueuePriority:NSOperationQueuePriorityNormal];
	}
	return self;
}

-(void)main {
    //by tom.lih  
    CallBackTool *tool = [CallBackTool create];
    [tool getSignature:uid :count];
    
/*
	CallBackTool *tool = [CallBackTool create];
	
	NSString *urlStr =  [[NSString alloc] initWithString:[tool getSignatureUrl:uid]];	
	NSURL *url = [NSURL URLWithString:urlStr];
	NSData *data = [[NSData alloc] initWithContentsOfURL:url];	
	NSMutableDictionary *signatures = nil;
	
	if (data != nil) {
		NSStringEncoding enc = CFStringConvertEncodingToNSStringEncoding (kCFStringEncodingGB_18030_2000);
		NSString *sign = [[NSString alloc] initWithData:data encoding:enc];
		signatures = [NSMutableDictionary dictionaryWithDictionary:[tool getSignature:sign]];
		[sign release];
	} else {
		signatures = [NSMutableDictionary dictionaryWithDictionary: [tool getSignature:@""]];
	}
    
    [signatures setValue:uid forKey:@"uid"];
    
	NoticationItem *item = [[[NoticationItem alloc] init] autorelease];
	item.data =  [NSMutableDictionary dictionaryWithDictionary:signatures];
	NSLog(@"item.data: %@", item.data);
	
	[[NSNotificationCenter defaultCenter] postNotificationName:NOTIFICATION_SIGNATUREDOWNLOADED object:item];
	
	[urlStr release];
	[data release];
*/
}

- (void) dealloc {
	[uid release];
	[super dealloc];
}

@end
