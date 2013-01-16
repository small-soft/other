//
//  AMPageControlView.m
//  AlibabaMobile
//
//  Created by cloud ma on 12-9-3.
//  Copyright (c) 2012年 alibaba. All rights reserved.
//

#import "AMPageControlView.h"


@interface AMPageControlView ()
@property (nonatomic,retain)UIScrollView *scrollView;

@property (nonatomic)BOOL pageControlUsed;
@end

@implementation AMPageControlView
@synthesize delegate=_delegate;
@synthesize scrollView=_scrollView;
@synthesize pageControl = _pageControl;
@synthesize pageControlUsed =_pageControlUsed;
@synthesize showPageControl=_showPageControl;
@synthesize autoScroll=_autoScroll;
-(void)dealloc
{
    [_scrollView release];
    [_pageControl release];
    
    [super dealloc];
}
-(UIScrollView*)scrollView
{
    if (!_scrollView) {
        _scrollView = [[UIScrollView alloc]init];
        _scrollView.frame = CGRectMake(0.0, 0.0, self.frame.size.width, self.frame.size.height);
        _scrollView.pagingEnabled = YES;
        _scrollView.showsHorizontalScrollIndicator = NO;
        _scrollView.showsVerticalScrollIndicator = NO;
        _scrollView.scrollsToTop = NO;
        _scrollView.bounces = NO;
        _scrollView.delegate = self;
        
    }
    return _scrollView;
}
-(AliPageControl*)pageControl
{
    if (!_pageControl) {
        _pageControl = [[AliPageControl alloc]init];
        _pageControl.frame = CGRectMake(0.0, self.frame.size.height - 20, self.frame.size.width, 20);
        _pageControl.currentPage = 0;
        [_pageControl addTarget:self action:@selector(pageControlValueChanged:) forControlEvents:UIControlEventValueChanged];
    }
    return _pageControl;
}

-(void)setDelegate:(id <AMPageControlViewDelegate> )delegate
{
    if (!_delegate) {
        _delegate = delegate;
        self.backgroundColor = [UIColor clearColor];
        [self addSubview:self.scrollView];
        if (self.showPageControl) {
            [self addSubview:self.pageControl];
        }
        
    }
}

-(void)reloadData
{
    self.scrollView.contentSize = CGSizeMake(self.frame.size.width * [self.delegate numberOfSectionsInGallaryView:self], self.frame.size.height);
    self.pageControl.numberOfPages = [self.delegate numberOfSectionsInGallaryView:self];
    self.pageControl.currentPage = 0;
    [self loadScrollViewWithPage:0];
      
}
- (void)loadScrollViewWithPage:(int)page
{
    if (page < 0)
        return;
    if (page >= [self.delegate numberOfSectionsInGallaryView:self])
        return;
    UIControl *view = [self.delegate AliGallaryView:self atIndex:page];
    
    if (view.superview == nil)
    {
        view.frame = CGRectMake(view.frame.size.width * page, 0.0, view.frame.size.width, view.frame.size.height);
        view.tag = page;
        
//        UITapGestureRecognizer * clickRecognizer = [[UITapGestureRecognizer alloc] init];
//        
//        [clickRecognizer addTarget:self action:@selector(viewTouchUpInside:)];
//        
//        [view addGestureRecognizer:clickRecognizer];
//        [clickRecognizer release];
        
        
        // [view addTarget:self action:@selector(viewTouchUpInside:) forControlEvents:UIControlEventTouchUpInside];
        [self.scrollView addSubview:view]; 
    }
    
}
-(void)viewTouchUpInside:(UIControl*)sender
{
    if ([self.delegate respondsToSelector:@selector(AliGallaryView:didAtIndex:)]) {
        
        [self.delegate AliGallaryView:self didAtIndex:self.pageControl.currentPage];
    }
}
/*
 DELEGATE
 */
-(void)scrollViewDidScroll:(UIScrollView *)sender
{
    
    if (self.pageControlUsed)
    {
        // do nothing - the scroll was initiated from the page control, not the user dragging
        return;
    }
    // Switch the indicator when more than 50% of the previous/next page is visible
    CGFloat pageWidth = self.scrollView.frame.size.width;
    int page = floor((self.scrollView.contentOffset.x - pageWidth / 2) / pageWidth) + 1;
    // load the visible page and the page on either side of it (to avoid flashes when the user starts scrolling
    self.pageControl.currentPage = page;
    
    [self loadScrollViewWithPage:page-1];
    [self loadScrollViewWithPage:page];
    [self loadScrollViewWithPage:page+1];
    
}
// At the begin of scroll dragging, reset the boolean used when scrolls originate from the UIPageControl
- (void)scrollViewWillBeginDragging:(UIScrollView *)scrollView
{
    self.pageControlUsed = NO;
}

// At the end of scroll animation, reset the boolean used when scrolls originate from the UIPageControl
- (void)scrollViewDidEndDecelerating:(UIScrollView *)scrollView
{
    self.pageControlUsed = NO;
}
@end

