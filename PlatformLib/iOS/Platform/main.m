// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

int main(int argc, char* argv[])
{
	NSAutoreleasePool*	pPool	= [[NSAutoreleasePool alloc] init];

	int	iRetVal	= UIApplicationMain(argc, argv, nil, @"SuperPlayDelegate");

	[pPool release];

    return	iRetVal;
}
