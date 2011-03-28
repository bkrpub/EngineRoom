#!/usr/bin/env perl -s 

use strict;
use warnings;

our $path = ".";

our $prefix ||= "logpoints";
our $name ||= "custom";

our $kinds ||= "switch assert trace debug info notice warning error";
our @kinds = split(/\s+/, $kinds);

our $count ||= 16;

our $tabWidth = 0 unless defined $tabWidth;

our $contexts ||= 'c objc';
our @contexts = split(/\s+/, $contexts);

our $default_macros ||= 0;
our $base_macros ||= 0;

sub default_macros( $ ) {

    my $config = shift;

    my $base = $config->{ base };

    my $zero = $config->{zero};

    my $kindFlags = $config->{kindFlags};

    my $kindConstant = $config->{kindConstant};

    my $v = $config->{v};

    my @c = ();
    
    foreach my $kind ( @{ $config->{kinds} } ) {

	my @cOn = ();
	my @cOff = ();
	my @cOnOff = ();
	my @cxxOn = ();
	my @cxxOff = ();
	my @cxxOnOff = ();
	my @objcOn = ();
	my @objcOff = ();
	my @objcOnOff = ();


	my $on = [ \@cOn, \@objcOn, \@cxxOn ];
	my $off = [ \@cOff, \@objcOff, \@cxxOff ];
	my $onOff = [ \@cOnOff, \@objcOnOff, \@cxxOnOff ];
	
	my $lcKind  = lc($kind);
	my $ucKind  = uc($kind);
	my $ucFirstKind = ucfirst($kind);
	
	for my $ctx ( @{ $config->{contexts} } ) {
	    
	    for my $useKeys ( @{ $config->{ keys } } ) {		
		
		my $inKeys = $useKeys ? "keys, " : "";
		my $outKeys = $useKeys ? "(keys)" : "kLogPointKeysNone";
		
		my $names = $config->{ names }->{ $kind } || $config->{ names }->{ default };
		
		my $name;

		
		if( $name = $names->{ printf } ) {
		    push @cOnOff,    qq<#define $name(${inKeys}fmt, ...) \a ${base}_${ctx}_printf$v($kindFlags, $kindConstant, $outKeys, kLogPointLabelNone, kLogPointFormatInfoNone, (fmt), ## __VA_ARGS__)>;
		}

		if( $name = $names->{ assert_printf } ) {
		    push @cOnOff,    qq<#define $name(${inKeys}cond, fmt, ...) \a ({ LOGPOINT *__lpRet = NULL; if( ! (cond) ) { __lpRet = ${base}_${ctx}_printf$v($kindFlags, $kindConstant, $outKeys, "(" #cond ")", kLogPointFormatInfoNone, (fmt), ## __VA_ARGS__); if( __lpRet ) { if( LOGPOINT_IS_ASSERT( *__lpRet ) ) { NSLog(@"ASSERTION - HARD - FIXME" ); } else { NSLog(@"ASSERTION - SOFT - FIXME"); } } } logPointReturnFromMacro(__lpRet); })>;
		}

		if( $name = $names->{ assert_auto_multiple } ) {
		    push @cOnOff,    qq<#define $name(${inKeys}cond, ...) \a ({ LOGPOINT *__lpRet = NULL; if( ! (cond) ) { __lpRet = ${base}_${ctx}_auto_multiple$v($kindFlags, $kindConstant, $outKeys, "(" #cond ")", ## __VA_ARGS__); if( __lpRet ) { if( LOGPOINT_IS_ASSERT( *__lpRet ) ) { NSLog(@"ASSERTION - HARD - FIXME" ); } else { NSLog(@"ASSERTION - SOFT - FIXME"); } } } logPointReturnFromMacro(__lpRet); })>;
		}

		
		if( $name = $names->{ auto_multiple } ) {
		    push @objcOnOff, qq<#define $name(${inKeys}...) \a ${base}_${ctx}_auto_multiple$v($kindFlags, $kindConstant, $outKeys, kLogPointLabelNone, ## __VA_ARGS__ )>;
		}
		
		if( $name = $names->{ auto_rvalue } ) {
		    push @objcOn,    qq<#define $name(${inKeys}value) \a ${base}_${ctx}_auto_rvalue$v( $kindFlags, $kindConstant, $outKeys, #value, (value) )>, "";
		    push @objcOff,   qq<#define $name(${inKeys}value) \a (value)>;
		}
		
		if( $name = $names->{ auto_return } ) {
		    push @objcOn,    qq<#define $name(${inKeys}value) \a return ${base}_${ctx}_auto_rvalue$v( $kindFlags, $kindConstant, $outKeys, "return", (value) )>, "";
		    push @objcOff,   qq<#define $name(${inKeys}value) \a return (value)>;
		}

		
		for( @$on, @$off, @$onOff ) {
		    
		    for( @$_ ) {
			
			my $pK = $useKeys ? $config->{ percentK } : '';
			s/%K/$pK/g;
			
			my $pC = $config->{ percentC }->{ $ctx } || '';
			s/%C/$pC/g;
			
		    }
		}
		
	    } # keys
	    
	} # contexts	
		
	for my $langIndex ( 0 .. @$on ) {
	    for( @{ $onOff->[$langIndex] } ) {
		push @{$on->[$langIndex]}, $_, "";
		my( $macro, $substitution ) = split(/ *\a */, $_);
		push @{$off->[$langIndex]}, length($substitution || '') ? "$macro \a $zero" : defined($macro) ? $macro : '';
	    }
	}
	
	push @c, "", "#if LOGPOINT_ENABLE_%U", "";
	push @c, "", @cOn;

	if( @objcOn ) {
	    push @c, "", "#if __OBJC__";
	    push @c, "", @objcOn;
	    push @c, "", "#endif", "/* __OBJC__ */";
	}
	 
	if( @cxxOn ) {
	    push @c, "", "#if __cplusplus";
	    push @c, "", @cxxOn;
	    push @c, "", "#endif", "/* __cplusplus */";
	}

	push @c, "", "#else", "/* ! LOGPOINT_ENABLE_%U */";

	push @c, "", @cOff;

	if( @objcOff ) {
	    push @c, "", "#if __OBJC__";
	    push @c, "", @objcOff;
	    push @c, "", "#endif", "/* __OBJC__ */";
	}

	if( @cxxOff ) {
	    push @c, "", "#if __cplusplus";
	    push @c, "", @cxxOff;
	    push @c, "", "#endif", "/* __cplusplus */";
	}

	push @c, "", "#endif", "/* LOGPOINT_ENABLE_%U */";

	for( @c ) {
	    s/%L/$lcKind/g;
	    s/%U/$ucKind/g;
	    s/%F/$ucFirstKind/g;
	}

    } # kinds



    
    return @c;
}

sub base_macros( % ) {
    my %p = @_;

    my $count = $p{ count } || 3;
    my $zero = $p{zero} || 'LOGPOINT_ZERO';
    my $base = $p{base} || 'lplog';

    my $ucBase = uc($base);

    my $contextFlags = {
	'c' => 'LOGPOINT_C',
	'cxx' => 'LOGPOINT_CXX',
	'objc' => 'LOGPOINT_OBJC',
    };

    my $contextLangSpecs = {
	'c' => 'NULL, NULL',
	'cxx' => 'this, NULL',
	'objc' => 'self, _cmd',
    };

    my @c = ();
    my @cOn = ();
    my @cOff = ();
    my @objcOn = ();
    my @objcOff = ();

    my @private = ();

    my $v = "_v1";

    my $autoArgcOffset = 4;

    
    push @c, "", 
    "#ifdef __OBJC__",
    "#import <Foundation/Foundation.h>",
    "#import <objc/runtime.h>",
    "#endif",
    "",
    qq<#include "logpoints_api.h">,
    "";

    for my $ctx ( @contexts ) {

	my $CTX = uc($ctx);

	my $extraFlags = " | $contextFlags->{$ctx}"; 
	my $langSpec = $contextLangSpecs->{$ctx}; 

	my @cOnOff = ();
	my @objcOnOff = ();
	

	push @cOnOff, qq<#define ${base}_${ctx}_printf$v(flags, kind, keys, label, fmtInfo, fmt, ...) \a LOGPOINT_CREATE((flags)$extraFlags, (kind), (keys), (label), $langSpec, (fmtInfo), (fmt), ## __VA_ARGS__)>, "";

	push @objcOnOff, qq<#define ${base}_${ctx}_auto_multiple$v(flags, kind, keys, label, ...) \a ER_VARARGS_TO_NONZERO_ARGS(_${base}_${ctx}_auto${v}_${autoArgcOffset}lessThan_, (flags)$extraFlags, (kind), (keys), (label), ## __VA_ARGS__)>, "";

	push @objcOn, qq<#define ${base}_${ctx}_auto_rvalue$v(flags, kind, keys, label, value) \a ({ \\
        __typeof__(value) __lpValueTmp = (value); \\
        id __lpMsg = LOGPOINT_FORMAT_VALUE(__lpValueTmp, kLogPointLabelNone); \\
        (void) LOGPOINT_CREATE( (flags)$extraFlags, (kind), (keys), (label), $langSpec, #value, "%@", __lpMsg ); \\
        __lpValueTmp; })>, "";

	push @objcOff, qq<#define ${base}_${ctx}_auto_rvalue$v(flags, kind, keys, label, value) \a (value)>, "";


	for my $objc ( 0 .. 1 ) {
	    for( $objc ? @objcOnOff : @cOnOff ) {
		push @{$objc ? \@objcOn : \@cOn}, $_;
		my( $macro, $substitution ) = split(/ *\a */, $_);
		push @{$objc ? \@objcOff : \@cOff}, length($substitution || '') ? "$macro \a $zero" : defined($macro) ? $macro : '';
	    }
	}

	for( my $i = 0 ; $i <= $count ; ++$i ) {

	    my $inArgs     = $i ?     join(", ",     "", map { "v$_" } 1 .. $i ) : "";
	    my $formatInfo = $i ?     join(' ", " ',     map { "#v$_" } 1 .. $i ) : "kLogPointFormatInfoNone";
	    my $format     = $i ? '"'.join("%s",         map { '%@' } 1 .. $i ).'"' : "kLogPointFormatNone";

#	    my $parameters = $i ?     join(", ", "",     map { qq< \\\n\t\t\tLOGPOINT_FORMAT_VALUE( (v$_), #v$_ )> } 1 .. $i ) : "";
	    my $parameters = $i ?     ", " . join(", LOGPOINT_PARAMETER_SEPARATOR, ", map { qq< \\\n\t\t\tLOGPOINT_FORMAT_VALUE( (v$_), #v$_ )> } 1 .. $i ) : "";
	    	    
	    my $argc = $i + $autoArgcOffset;

	    push @private, qq<#define _${base}_${ctx}_auto${v}_${autoArgcOffset}lessThan_${argc}(flags, kind, keys, label$inArgs) \a LOGPOINT_CREATE((flags)$extraFlags, (kind), (keys), (label), $langSpec, $formatInfo, $format$parameters)>;
	    
	}


    }

    push @c, "", "#if LOGPOINT_ENABLE_${ucBase}", "";
    push @c, "", @cOn;
    push @c, "", "#if __OBJC__", "/* currently no auto support for C or CXX - see experimental */";
    push @c, "", @objcOn;
    push @c, "", "#endif", "/* __OBJC__ */";
    push @c, "", "#else", "/* ! LOGPOINT_ENABLE_${ucBase} */";
    push @c, "", @cOff;
    push @c, "", "#if __OBJC__", "/* currently no auto support for C or CXX - see experimental */";
    push @c, "", @objcOff;
    push @c, "", "#endif", "/* __OBJC__ */";
    push @c, "", "#endif", "/* LOGPOINT_ENABLE_${ucBase} */";

    push @c, "", "/* ==================================================== */";
    push @c,     "/* ==== PRIVATE PARTS - will change without notice ==== */";
    push @c,     "/* ==================================================== */";

    push @c, "", "/* used by auto-varargs macro ER_VARARGS_TO_NONZERO_ARGS */", "";

    push @c, "", @private, "";


    return @c;
}


sub beautify ( @ ) {
    my @c = @_;
    my(@macros) = ();
    my(@substitutions) = ();
    my $maxLength = 0;

    for( @c ){
	my( $macro, @rest ) = split(/ *[\a] */, $_);
	next unless @rest;
	$maxLength = length($macro) if length($macro) > $maxLength;
    }

    my $code = join("\n", "", ( map {
	my( $macro, @rest ) = split(/ *[\a] */, $_);
	my $sep = " ";
	$macro = "" unless defined $macro;
	@rest ? sprintf("%-*s%s%s", ($macro =~ /\\$/) ? 0 : $maxLength, $macro, 
			$sep,
			join($sep, @rest)) : $macro;
			    } @c), "");

    $tabWidth and $code =~ s/ {$tabWidth}/\t/g;

    $code =~ s/\n{2,}/\n\n/g;

    return $code;
}


sub write_header {
    my $path = shift;
    my $file = shift;
    my @payload = @_;
    my @content = ();

    my $marker = $file;
    $marker =~ s/\./_/g;
    $marker = '__' . uc($marker) . '__';
    
    push @content, "/*", " * $file - generated code - do not edit", " */", "";

    push @content, "#ifndef $marker", "#define $marker 1", "";

    push @content, @payload;

    push @content, "", "#endif", "/* $marker */", "";

    my $output = "$path/$file";
    open(FILE, ">", $output) or die "can't open $output for writing ($!)\n";
    print FILE beautify( @content );
    close(FILE);

    return 0;
}


sub main() {

    my @content = ();
    my @payload = ();

    if ( $base_macros ) {
	$name = "base_macros";

	push @payload, "", base_macros( count => $count, kind => 'log' ), "";

    }

    if ( $default_macros ) {
	$name = "default_macros";

	push @payload, "", qq<#include "logpoints_base_macros.h">, "";

	my $config = {

	    # version suffix of macros
	    v => '_v1',
	    
	    kinds => [ @kinds ],
	    
	    # basename of api macros
	    base => 'lplog',
	    
	    kindFlags => "LOGPOINT_FLAGS_%U",
	    
	    kindConstant =>  "kLogPointKind%F",
	    
	    zero => 'LOGPOINT_ZERO',
	    
	    # language contexts (functions / methods) to generate macros for
	    contexts => [ qw( c objc ) ], # cxx is not yet supported
	    
	    percentC => {
		c => 'c',
		objc => '',
		cxx => 'p',
	    },
	    
	    percentK => 'k',
	    
	    # number of macros to generate for auto-argument-count
	    count => $count, 
	    
	    # array of values for "useKeys" to generate for
	    keys => [ 0 .. 1 ], 
	    
	    # %K: value of percentK if producing a macro which uses keys, else '' 
	    # %C: value of percentC->{ context } if producing a macro which uses keys
	    # %L: lowercase kind
	    # %U: uppercase kind
	    # %F: uppercase first letter kind
	    
	    names => {
		
		'default' => {
		    printf => 'lp%K%C%Lf',
		    auto_multiple => 'lp%K%C%L',
		    auto_rvalue => 'lp%K%C%L_expr',
		    auto_return => 'return_lp%K%C%L',
		},
		
		'switch' => {
		    printf => 'lp%K%C%Lf',
		    auto_multiple => 'lp%K%C%L',
		},
		
		'assert' => {
		    assert_printf => 'lp%K%C%Lf',
		    assert_auto_multiple => 'lp%K%C%L',
		    #auto_rvalue => 'lp%K%C%L_expr',
		    #auto_return => 'return_lp%K%C%L',
		},
	    },

	};

	
	push @payload, "", default_macros( $config );
    }

    my $file  = $prefix . '_' . $name . '.h';

    write_header( $path, $file, @payload );

}


exit &main;


=pod

/* no non-objC AUTO support right now - there is some stuff in experimental for plain c but it is gruesome */

lpsingle

#define lpInt(keys, ...)            LOGPOINT_ZERO
#define lpcInt(keys, ...)           LOGPOINT_ZERO

#define lpDouble(keys, ...)         LOGPOINT_ZERO
#define lpcDouble(keys, ...)        LOGPOINT_ZERO

#define lpshow(v)    LOGPOINT_ZERO
#define lpcshow(v)    LOGPOINT_ZERO

=cut

