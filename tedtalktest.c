// File: tedtalktest.c 
// 
// Description: test the tedtalk.c module
// @author      RIT CS Instructors
// 
// // // // // // // // // // // // // // // // // // // // // // // // 

//
// Content supplied to the student.
//

#include <stdio.h>
#include <stdlib.h>

#include "tedtalk.h"
#include "EventTime.h"

/// main function tests the tedtalk module.
/// @returns errorCode  error Code; EXIT_SUCCESS if no error

int main( void ) {
    //the four items we will use
    EventTime_t * atime = NULL ;
    TEDtalk_t * talk1 = NULL ;
    TEDtalk_t * talk2 = NULL ;
    TEDtalk_t * talk3 = NULL ;
    // setting things up
    printf( "Creating a time...\n" ) ;
    // creates a new event time at 6:30pm
    atime = newEventTime( 6, 30, "pm" ) ;

    printf( "Starting tedtalk tests...\n" ) ;
    // creates a new TEDtalk titled "Do schools..." by "Ken Robin..."
    // talk1 is not freed from memory, must add before resetting it
    talk1 = newTEDtalk( "Do schools kill creativity?", "Ken Robinson" ) ;
    printf( "First tedtalk initialized...\n" ) ;

    // gets our speaker and title of presentation
    char * speaker = tedtalkGetSpeaker( talk1 ) ;
    char * title = tedtalkGetTitle( talk1 ) ;
    // prints them out
    printf( "The current tedtalk is: \n\t%s by %s.\n", title, speaker) ;
    // frees our two dynamically allocated memory items
    free( speaker ) ;
    free( title ) ;

    // gets the string representation of talk1 and prints it (thinking ahead
    // we never free mstr, prolly not too good)
    char * mstr = tedtalkToString( talk1 ) ;
    printf( "Otherwise... %s\n", mstr ) ;

    // plays talk1 at atime
    tedtalkPlay( talk1, atime ) ;
    // gets our mstr again and prints it
    mstr = tedtalkToString( talk1 ) ;
    printf( "After playing the tedtalk... \n\t%s\n", mstr ) ;

    // gets a pointer to the last time talk1 was played
    EventTime_t * glp = tedtalkGetLastPlayed( talk1 ) ;
    // gets string representation of glp
    char * sglp = timeToString(glp) ;
    // gets speaker of talk1
    speaker = tedtalkGetSpeaker( talk1 ) ;
    // gets title of talk1
    title = tedtalkGetTitle( talk1 ) ;
    // prints the things we just got
    printf( "The same tedtalk referencing members is: \n\t%s by %s. Last played at: %s\n",
             title, speaker, sglp ) ;
    // frees our things
    free( speaker ) ;
    free( title ) ;
    timeDelete( glp ) ;
    free( sglp ) ;

    // deletes our talk1
    tedtalkDelete( talk1 ) ;
    // frees talk1 from dynamic memory (var reused later, prevents memory leak)
    free( talk1 );


    speaker = malloc( strlen( "Amy Cuddy" ) + 1 ) ;
    title = malloc( strlen( "Your body shapes who you are" ) + 1 ) ;
    strcpy( speaker, "Amy Cuddy" ) ;
    strcpy( title, "Your body shapes who you are" ) ;
    // construts talk2 with title and speaker
    talk2 = newTEDtalk( title, speaker ) ;
    // frees title and speaker
    free( speaker ) ;
    free( title ) ;
    // gets string representation of talk2 and prints it
    mstr = tedtalkToString( talk2 ) ;
    printf( "The talk2 is: \n\t%s\n", mstr ) ;


    // copies talk2 into talk1
    talk1 = tedtalkCopy( talk2 ) ;
    // gets the string representation of talk1 and prints it
    mstr = tedtalkToString( talk1 ) ;
    printf( "The copy of talk2 tedtalk is: \n\t%s \n", mstr ) ;
    // deletes talk2
    tedtalkDelete( talk2 ) ;
    // gets string representationof talk1 again and prints it (to show it was
    // properly copied over)
    mstr = tedtalkToString( talk1 ) ;
    printf( "After deleting the original talk2, the copy of talk2 "
            "tedtalk is ... \n\t%s\n", mstr ) ;

    // creates a new char pointer named pstr
    char * pstr ;
    // copies talk1 into talk3
    talk3 = tedtalkCopy( talk1 ) ;
    // performs an equality check on talk1 and talk3
    if ( tedtalkEquals( talk1, talk3 ) ) {
        // if they're equal, get strint representation of talk1
        mstr = tedtalkToString( talk1 ) ;
        // gets string representation of talk3
        pstr = tedtalkToString( talk3 ) ;
        // prints talk3 and talk1
        printf( "The talk3 tedtalk \n\t%s\n"
                "    is the same as this tedtalk \n\t%s\n", pstr, mstr ) ;
        // frees pstr
        free( pstr ) ;
    } else {
        // if talk1 and talk3 aren't equal we report it here
        printf( "ERROR: tedtalkCopy() failure!\n" ) ;
    }

    // deletes talk3
    tedtalkDelete( talk3 ) ;
    // frees talk3 from dynamic memory (var reused later, prevents memory leak)
    free( talk3 );
    // deltes talk1
    tedtalkDelete( talk1 ) ;
    // frees talk1 from dynamic memory (var reused later, prevents memory leak)
    free( talk1 );

    // creates a new TED talk and puts it in talk3
    talk3 = newTEDtalk( "How great leaders inspire action", "Simon Sinek" ) ;
    // gets string representation of talk3 and prints it
    mstr = tedtalkToString( talk3 ) ;
    printf( "The current talk3 tedtalk is: \n\t%s\n", mstr ) ;

    // plays talk3 at 4:42 am (newEventTime uses dynamic mem. never cleared)
    tedtalkPlay( talk3, newEventTime(4, 42, "am") ) ;
    // gets new string representation of talk3 and prints it
    mstr = tedtalkToString( talk3 ) ;
    printf( "The current talk3 tedtalk is: \n\t%s\n", mstr ) ;
    // frees mstr
    free( mstr ) ;

    // deletes talk3
    tedtalkDelete( talk3 ) ;
    // frees talk3 from dynamic memory
    free( talk3 );

    return EXIT_SUCCESS ;
}
