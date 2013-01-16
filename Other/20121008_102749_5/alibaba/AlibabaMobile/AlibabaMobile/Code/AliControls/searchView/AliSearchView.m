//
//  AliSearchView.m
//  AlibabaMobile
//
//  Created by alimobile on 12-4-12.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AliSearchView.h"

#import "searchViewDef.h"
#import "searchBarSelectView.h"
#import "searchBarEditView.h"
#import "searchBarCancelView.h"
#import "AMSearchResultData.h"
#define SEARCHBAR_START_X 5.0
#define SEARCHBAR_END_X 5.0


@interface AliSearchView()
@property (nonatomic,retain)UIImageView*backgroundView;
@property (nonatomic,retain)searchBarSelectView*selectedView;
@property (nonatomic,retain)searchBarCancelView*cancelView;
@property (nonatomic,retain)searchPickerView*searchPicker;
@property (nonatomic,retain)searchHistoryTable*searchHistory;
@property (nonatomic,retain)AMSearchResultData*searchResultData;
@property (nonatomic)BOOL editing;

@end

@implementation AliSearchView
@synthesize delegate=_delegate;
@synthesize backgroundView = _backgroundView;
@synthesize selectedView=_selectedView;
@synthesize searchPicker=_searchPicker;
@synthesize searchHistory = _searchHistory;
@synthesize editView=_editView;
@synthesize cancelView = _cancelView;
@synthesize editing=_editing;
@synthesize searchResultData = _searchResultData;
-(void)dealloc
{
    //[_delegate release];
    //_delegate = nil;
    [self.searchPicker removeFromSuperview];
    [self.searchHistory removeFromSuperview];
    [_backgroundView release];
    [_selectedView release];
    [_editView release];
    [_cancelView release];
    //[_searchPicker release];
    _searchPicker = nil;
    //[_searchHistory release];
    _searchHistory = nil;
    [_searchResultData release];
    [super dealloc];
}

-(UIImageView*)backgroundView
{
    if (!_backgroundView) {

        _backgroundView = [[UIImageView alloc]initWithFrame:CGRectMake(0.0, 0.0, self.frame.size.width, self.frame.size.height)];
//        [_backgroundView sizeToFit];
        _backgroundView.backgroundColor = [UIColor colorWithRed:255/255.0f green:115/255.0f blue:0/255.0f alpha:1.0f];
//        _backgroundView.frame = CGRectMake(0.0, 0.0, _backgroundView.frame.size.width, _backgroundView.frame.size.height);
    }
    return _backgroundView;
}

-(searchBarSelectView*)selectedView
{
    if (!_selectedView) {
        _selectedView = [searchBarSelectView createView];
        [_selectedView addTarget:self action:@selector(selectViewUpInsideAction:)  forControlEvents:UIControlEventTouchUpInside];
        [_selectedView addTarget:self action:@selector(selectViewDownAction:)  forControlEvents:UIControlEventTouchDown];
        [_selectedView addTarget:self action:@selector(selectViewUpOutsideAction:)  forControlEvents:UIControlEventTouchUpOutside];
        _selectedView.selectedState = SEARCH_PRODUCT;
        _selectedView.frame = CGRectMake(5, 0.0, _selectedView.frame.size.width, _selectedView.frame.size.height);
    }
    return _selectedView;
}
-(searchBarEditView*)editView
{
    if (!_editView) {
        _editView = [searchBarEditViewWithImage createView];  
        [_editView.editTextField addTarget:self action:@selector(searchBarEditViewEditBegin:) forControlEvents:UIControlEventEditingDidBegin];
        [_editView.editTextField addTarget:self action:@selector(searchBarEditViewDidEnd:) forControlEvents:UIControlEventEditingDidEndOnExit];
        [_editView.editTextField addTarget:self action:@selector(searchBarEditViewEditChanged:) forControlEvents:UIControlEventEditingChanged];
        [_editView.deleteButton addTarget:self action:@selector(deleteButtonPressed:) forControlEvents:UIControlEventTouchUpInside];
    }
//    CGFloat startX=SEARCHBAR_START_X+self.selectedView.frame.size.width;
    CGFloat startX=SEARCHBAR_START_X;
    CGFloat editViewWidth = 0;

    if (self.editing) {
        editViewWidth = self.frame.size.width-SEARCHBAR_END_X-startX - self.cancelView.frame.size.width-10;

    }
    else {
        editViewWidth = self.frame.size.width-SEARCHBAR_END_X-startX;

    }
    
    _editView.frame = CGRectMake(startX, 0.0, editViewWidth, _editView.frame.size.height);

    return _editView;
}



-(searchBarCancelView*)cancelView
{
    if(!_cancelView)
    {
        _cancelView = [searchBarCancelView createView];
        _cancelView.hidden=YES;
        [_cancelView.cancelButton addTarget:self action:@selector(cancelButtonTouchUpInside:) forControlEvents:UIControlEventTouchUpInside];
    }
    CGFloat startX;
    if (self.editing) {
        startX = self.frame.size.width- SEARCHBAR_END_X-_cancelView.frame.size.width;
        
    }
    else {
        startX = self.frame.size.width;
        
    }
    
    _cancelView.frame = CGRectMake(startX, 0.0, _cancelView.frame.size.width, _cancelView.frame.size.height);

    return _cancelView;
}


-(searchPickerView*)searchPicker
{
    if (!_searchPicker) {
        _searchPicker = [searchPickerView createView];
        _searchPicker.hidden = YES;
     
        [_searchPicker setTag:11];
        //[self.superview addSubview:_searchPicker];
        //_searchPicker.frame = CGRectMake(0, self.frame.origin.y+self.frame.size.height, _searchPicker.frame.size.width, _searchPicker.frame.size.height);
        _searchPicker.frame = CGRectMake(0, self.frame.origin.y+self.frame.size.height, _searchPicker.frame.size.width, _searchPicker.frame.size.height);
        _searchPicker.delegate = self;
    }
    
    return _searchPicker;
}
-(searchHistoryTable*)searchHistory
{
    if (!_searchHistory) {
        _searchHistory = [searchHistoryTable createView];
        _searchHistory.hidden=YES;
        _searchHistory.delegate = self;
        [_searchPicker setTag:12];
       //[self.superview insertSubview:_searchHistory belowSubview:self.searchPicker];
         _searchHistory.frame = CGRectMake(0.0, self.frame.origin.y+self.frame.size.height, _searchHistory.frame.size.width, _searchHistory.frame.size.height);
    }
        
    
    return _searchHistory;
}

-(void)setDelegate:(NSObject<AliSearchViewDelegate> *)delegate
{
    if (!_delegate) {
        _delegate=delegate;
        
      } 
}
//当edit状态变动则考虑如何隐藏cancelView
-(void)setEditing:(BOOL)editing
{
    _editing = editing;
    [UIView beginAnimations:@"filpping" context:nil];
    [UIView setAnimationDuration:0.2];
    self.editView.hidden=NO;
    if (editing) {
        self.cancelView.hidden=NO;
    }
    else {
        self.cancelView.hidden=YES;
    }
    [UIView commitAnimations];
}
-(AMSearchResultData*)searchResultData
{
    if (_searchResultData==nil) {
        _searchResultData = [[AMSearchResultData alloc]init];
    }
    return _searchResultData;
}
-(void)awakeFromNib
{
    [super awakeFromNib];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(keyboardWillShow:) name:UIKeyboardWillShowNotification object:nil]; 
    [self setupViews];
}
-(void)setupViews
{
//    [self addSubview:self.backgroundView];
    self.backgroundColor = [UIColor colorWithRed:255/255.0f green:115/255.0f blue:0/255.0f alpha:1.0f];
    
//    [self addSubview:self.selectedView];
    [self.editView addSubview:self.selectedView];
    [self addSubview:self.editView]; 
    [self addSubview:self.cancelView];  
    [self.superview addSubview:self.searchPicker]; 
    [self.superview insertSubview:self.searchHistory belowSubview:self.searchPicker];
        
}
-(void)editBecomeFirstResponder
{
    [self.editView.editTextField becomeFirstResponder];
}

-(void)historyBecomeFirstResponder{
    self.searchHistory.hidden = NO;
}

-(void)gotoSearch:(NSString*)content selected:(NSUInteger)selected
{
    [self.searchResultData saveData:content];
    [self.searchHistory  reloadResultData];
#warning xiugairen 孟希羲
    if ([(NSObject *)(self.delegate) respondsToSelector:@selector(searchBarEditViewDidEnd:content:selected:)])
    {
        [self.delegate searchBarEditViewDidEnd:self content:content selected:self.selectedView.selectedState];
    }
    
}

/*
 ACTION
 */
-(IBAction)selectViewUpInsideAction:(id)sender
{
    
    if (self.searchPicker.hidden) {
         self.searchPicker.hidden = NO;
        self.searchPicker.myView.alpha = 0.5;
        self.selectedView.identifyImage.image = [UIImage imageNamed:@"search_drop01_n"];
    }
    else {
        self.searchPicker.hidden = YES;
         self.searchPicker.myView.alpha = 0.0;
        self.selectedView.identifyImage.image = [UIImage imageNamed:@"search_drop_n"];
    }
}
-(IBAction)selectViewUpOutsideAction:(id)sender
{
    
    if (self.searchPicker.hidden) {
        self.selectedView.identifyImage.image = [UIImage imageNamed:@"search_drop_n"];
    }
    else {
        self.selectedView.identifyImage.image = [UIImage imageNamed:@"search_drop01_n"];
    }
}
-(IBAction)selectViewDownAction:(id)sender
{
    
    if (self.searchPicker.hidden) {
        self.selectedView.identifyImage.image = [UIImage imageNamed:@"search_drop_p"];
    }
    else {
        self.selectedView.identifyImage.image = [UIImage imageNamed:@"search_drop01_p"];
    }
}



-(IBAction)searchBarEditViewEditBegin:(id)sender
{
    self.editing=YES;
    self.searchPicker.hidden = YES;
//    self.searchHistory.hidden = YES;
    [self.searchHistory handleSearchForTerm:nil];
    [self.editView refreshInputState];
#warning xiugairen 孟希羲
    if ([(NSObject *)self.delegate respondsToSelector:@selector(searchBarEditViewEditBegin:)])
    {
        [self.delegate searchBarEditViewEditBegin:self];
    }
    self.searchHistory.hidden = NO;
}
-(IBAction)searchBarEditViewDidEnd:(UITextField*)sender
{
    [self gotoSearch:sender.text selected:self.selectedView.selectedState];
    self.editView.editTextField.text=@"";
    self.editing=NO;
    
}
-(IBAction)searchBarEditViewEditChanged:(UITextField*)sender
{
    [self.searchHistory handleSearchForTerm:sender.text];
    [self.editView refreshInputState];
}

- (IBAction)cancelButtonTouchUpInside:(id)sender {
    [self.searchHistory handleSearchForTerm:nil];
    
    self.editing = NO;
    self.editView.editTextField.text = @"";
    [self.editView.editTextField resignFirstResponder];
    self.searchPicker.hidden = YES;
//    self.searchHistory.hidden = YES;
    self.searchHistory.hidden = YES;
#warning xiugairen 孟希羲
    if ([(NSObject *)self.delegate respondsToSelector:@selector(searchBarEditCancel:)])
    {
        [self.delegate searchBarEditCancel:self];
    }
}
- (IBAction)deleteButtonPressed:(id)sender {
    self.editView.editTextField.text=@"";
}

- (void)keyboardWillShow:(NSNotification *)notification  
{  
//    NSDictionary *info = [notification userInfo];  
//    CGSize kbSize = [[info objectForKey:UIKeyboardFrameEndUserInfoKey] CGRectValue].size;  
//      NSLog(@"keyboardWillShow %f",self.searchHistory.frame.size.height);

    //[self searchPicker];
    //[self searchHistory];
    //NSLog(@"_searchPicker.frame.size.width : %f",self.searchPicker.frame.size.width);
    //self.searchPicker.frame = CGRectMake(SEARCHBAR_START_X, self.frame.origin.y+self.frame.size.height, self.searchPicker.frame.size.width, self.searchPicker.frame.size.height);
    
//    self.searchHistory.frame = CGRectMake(0.0, self.frame.origin.y+self.frame.size.height, self.searchHistory.frame.size.width, 460 - kbSize.height -(self.frame.origin.y+self.frame.size.height) );
        //self.searchHistory.frame = CGRectMake(0.0, self.frame.origin.y+self.frame.size.height, self.searchHistory.frame.size.width, 460 -(self.frame.origin.y+self.frame.size.height) );
    //自适应代码  
}  
//delegate
- (void)searchHistoryTable:(searchHistoryTable *)tableView didSelectRow:(NSString *)content
{
    [self gotoSearch:content selected:self.selectedView.selectedState];
}
- (void)searchHistoryTable:(searchHistoryTable *)tableView rowEdit:(NSString *)content
{
    self.editView.editTextField.text = content;
}
-(void)searchPickerView:(searchPickerView*)picker selected:(NSUInteger)selectedPicker
{
    self.selectedView.selectedState = selectedPicker;
    self.selectedView.identifyImage.image = [UIImage imageNamed:@"search_drop_n"];
    self.searchPicker.hidden = YES;
    self.searchPicker.myView.alpha = 0.0;
}
-(void)searchPickerViewWillAppear:(searchPickerView*)picker
{
    self.searchPicker.hidden = YES;
    self.searchPicker.myView.alpha = 0.0;
    self.selectedView.identifyImage.image = [UIImage imageNamed:@"search_drop_n"];
}
@end
