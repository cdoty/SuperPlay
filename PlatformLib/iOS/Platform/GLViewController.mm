#import "GLViewController.h"

//#define	ARCADIE

@implementation GLViewController

- (void) viewDidLoad
{
    CGRect	screenBounds	= [[UIScreen mainScreen] bounds];

    // Can this be set from the view somehow?
	self.view.frame	= screenBounds;

	[super viewDidLoad];
}

- (BOOL) shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)_interfaceOrientation
{
#ifdef ARCADIE
	if (UIInterfaceOrientationPortrait == _interfaceOrientation)
	{
		return	YES;
	}
#else
	if (UIInterfaceOrientationLandscapeRight == _interfaceOrientation || UIInterfaceOrientationLandscapeLeft == _interfaceOrientation)
	{
		return	YES;
	}
#endif

	return	NO;
}

- (NSUInteger) supportedInterfaceOrientations
{
#ifdef ARCADIE
	return	UIInterfaceOrientationMaskPortrait;
#else
	return	UIInterfaceOrientationMaskLandscape;
#endif
}

@end
