#!/usr/bin/env perl -s 

use strict;
use warnings;

our $path = ".";

our $prefix ||= "logpoints";
our $name ||= "custom";
our $kinds ||= "switch assert debug info notice warning error";
our $count ||= 10;

our $contexts ||= '_c _objc _cxx';
our @contexts = split(/\s+/, $contexts);

our $default_macros ||= 0;
our $api_macros ||= 0;

sub default_macros( % ) {
    my %p = @_;

    my $public = $p{ public } || 0;

    my $count = $p{ count } || 3;
    my $prefix = $p{ prefix } || 'lp';
    my $cPrefix = $p{ cPrefix } || ( $prefix . 'c' );
    my $keyedPrefix = $p{ keyedPrefix } || ( $prefix . 'k' );
    my $keyedCPrefix = $p{ keyedCPrefix } || ( $keyedPrefix . 'c' );
    my $kind = $p{ kind} || 'debug';
    my $lcKind  = $p{lcKind} || lc($kind);
    my $ucKind  = $p{ucKind} || uc($kind);
    my $ucFirstKind = $p{ucFirstKind} || ucfirst($kind);
    my $zero = $p{zero} || 'LOGPOINT_ZERO';

    my $kindFlags = $p{ flags } || "LOGPOINT_FLAGS_${ucKind}";

    my $kindConstant = $p{kindConstant} || "kLogPointKind${ucFirstKind}";

    my $prefixKind = "$prefix$lcKind";
    my $cPrefixKind = "$cPrefix$lcKind";

    my $keyedPrefixKind = "$keyedPrefix$lcKind";
    my $keyedCPrefixKind = "$keyedCPrefix$lcKind";

    my $prefixKindF = $p{prefixKindF} || "${prefixKind}f"; 
    my $cPrefixKindF = $p{cPrefixKindF} || "${cPrefixKind}f"; 

    my $keyedPrefixKindF = $p{keyedPrefixKindF} || "${keyedPrefixKind}f"; 
    my $keyedCPrefixKindF = $p{keyedCPrefixKindF} || "${keyedCPrefixKind}f"; 

    my $prefixKindN = $p{prefixKindN} || "${prefixKind}"; 
    my $cPrefixKindN = $p{cPrefixKindN} || "${cPrefixKind}"; 

    my $keyedPrefixKindN = $p{keyedPrefixKindN} || "${keyedPrefixKind}"; 
    my $keyedCPrefixKindN = $p{keyedCPrefixKindN} || "${keyedCPrefixKind}"; 

    my $prefixKindX = $p{prefixKindX} || "${prefixKind}_value"; 
    my $cPrefixKindX = $p{cPrefixKindX} || "${cPrefixKind}_value"; 

    my $keyedPrefixKindX = $p{keyedPrefixKindX} || "${keyedPrefixKind}_value"; 
    my $keyedCPrefixKindX = $p{keyedCPrefixKindX} || "${keyedCPrefixKind}_value"; 

    my $prefixKindR = $p{prefixKindR} || "${prefixKind}_return"; 
    my $cPrefixKindR = $p{cPrefixKindR} || "${cPrefixKind}_return"; 

    my $keyedPrefixKindR = $p{keyedPrefixKindR} || "${keyedPrefixKind}_return"; 
    my $keyedCPrefixKindR = $p{keyedCPrefixKindR} || "${keyedCPrefixKind}_return"; 

    my @c = ();

    my @cOn = ();
    my @cOff = ();
    my @cOnOff = ();
    my @objcOn = ();
    my @objcOff = ();
    my @objcOnOff = ();

    my $v = "_v1";

    push @cOnOff, qq<#P#define $keyedPrefixKindF(keys, fmt, ...) \a lplog_objc_printf$v($kindFlags, $kindConstant, (keys), kLogPointLabelNone, kLogPointFormatInfoNone, (fmt), ## __VA_ARGS__)>;
    push @cOnOff, qq<#P#define $keyedCPrefixKindF(keys, fmt, ...) \a lplog_c_printf$v($kindFlags, $kindConstant, (keys), kLogPointLabelNone, kLogPointFormatInfoNone, (fmt), ## __VA_ARGS__)>;
    push @cOnOff, "";


    push @objcOnOff, qq<#P#define $keyedPrefixKindN(keys, ...) \a lplog_objc_auto_multiple$v($kindFlags, $kindConstant, (keys), kLogPointLabelNone, ## __VA_ARGS__ )>;
    push @objcOnOff, qq<#P#define $keyedCPrefixKindN(keys, ...) \a lplog_c_auto_multiple$v($kindFlags, $kindConstant, (keys), kLogPointLabelNone, ## __VA_ARGS__ )>;
    push @objcOnOff, "";

    push @objcOn, qq<#P#define $keyedPrefixKindX(keys, value) \a lplog_objc_auto_rvalue$v( $kindFlags, $kindConstant, (keys), #value, (value) )>;
    push @objcOn, qq<#P#define $keyedCPrefixKindX(keys, value) \a lplog_c_auto_rvalue$v( $kindFlags, $kindConstant, (keys), #value, (value) )>;
    push @objcOn, "";

    push @objcOff, qq<#P#define $keyedPrefixKindX(keys, value) \a (value)>;
    push @objcOff, qq<#P#define $keyedCPrefixKindX(keys, value) \a (value)>;
    push @objcOff, "";

    push @objcOn, qq<#P#define $keyedPrefixKindR(keys, value) \a lplog_objc_auto_return$v( $kindFlags, $kindConstant, (keys), "return", (value) )>;
    push @objcOn, qq<#P#define $keyedCPrefixKindR(keys, value) \a lplog_c_auto_return$v( $kindFlags, $kindConstant, (keys), "return", (value) )>;
    push @objcOn, "";

    push @objcOff, qq<#P#define $keyedPrefixKindR(keys, value) \a return (value)>;
    push @objcOff, qq<#P#define $keyedCPrefixKindR(keys, value) \a return (value)>;
    push @objcOff, "";

    for( @objcOnOff ) {
	push @objcOn, $_;
	s/#P#/#/;
	my( $macro, $substitution ) = split(/ *\a */, $_);
	push @objcOff, length($substitution || '') ? "$macro \a $zero" : defined($macro) ? $macro : '';
    }

    for( @cOnOff ) {
	push @cOn, $_;
	s/#P#/#/;
	my( $macro, $substitution ) = split(/ *\a */, $_);
	push @cOff, length($substitution || '') ? "$macro \a $zero" : defined($macro) ? $macro : '';
    }

    push @c, "", "#if LOGPOINT_ENABLE_${ucKind}", "";

    push @c, "#if __OBJC__", "/* currently no value-detect support for C or CXX - see experimental */";
    push @c, "", @objcOn;
    push @c, "", "#endif", "/* __OBJC__ */";
    push @c, "", @cOn;
    push @c, "", "#else", "/* ! LOGPOINT_ENABLE_${ucKind} */";
    push @c, "", "#if __OBJC__", "/* currently no value-detect support for C or CXX - see experimental */";
    push @c, "", @objcOff;
    push @c, "", "#endif", "/* __OBJC__ */";
    push @c, "", @cOff;
    push @c, "", "#endif", "/* LOGPOINT_ENABLE_${ucKind} */";

    push @c, "", "/* non-keyed variants */";


    push @c, qq<#P#define $prefixKindF(fmt, ...) \a $keyedPrefixKindF(kLogPointKeysNone, (fmt), ## __VA_ARGS__)>;
    push @c, qq<#P#define $cPrefixKindF(fmt, ...) \a $keyedCPrefixKindF(kLogPointKeysNone, (fmt), ## __VA_ARGS__)>;
    push @c, qq<#P#define $prefixKindN(...) \a $keyedPrefixKindN(kLogPointKeysNone, ## __VA_ARGS__)>;
    push @c, qq<#P#define $cPrefixKindN(...) \a $keyedCPrefixKindN(kLogPointKeysNone, ## __VA_ARGS__)>;
    push @c, qq<#P#define $prefixKindX(value) \a $keyedPrefixKindX(kLogPointKeysNone, (value))>;
    push @c, qq<#P#define $cPrefixKindX(value) \a $keyedCPrefixKindX(kLogPointKeysNone, (value))>;
    push @c, qq<#P#define $prefixKindR(value) \a $keyedPrefixKindR(kLogPointKeysNone, (value))>;
    push @c, qq<#P#define $cPrefixKindR(value) \a $keyedCPrefixKindR(kLogPointKeysNone, (value))>;

    return @c;
}

sub api_macros( % ) {
    my %p = @_;

    my $count = $p{ count } || 3;
    my $zero = $p{zero} || 'LOGPOINT_ZERO';
    my $base = $p{base} || 'lplog';

    my $ucBase = uc($base);

    my $contextFlags = {
	'_c' => 'LOGPOINT_C',
	'_cxx' => 'LOGPOINT_CXX',
	'_objc' => 'LOGPOINT_OBJC',
    };


    my $contextLangSpecs = {
	'_c' => 'NULL, NULL',
	'_cxx' => 'this, NULL',
	'_objc' => 'self, _cmd',
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
	

	push @cOnOff, qq<#P#define ${base}${ctx}_printf$v(flags, kind, keys, label, fmtInfo, fmt, ...) \a LOGPOINT_CREATE((flags)$extraFlags, (kind), (keys), (label), $langSpec, (fmtInfo), (fmt), ## __VA_ARGS__)>, "";


	push @objcOnOff, qq<#P#define ${base}${ctx}_auto_multiple$v(flags, kind, keys, label, ...) \a ER_VARARGS_TO_NONZERO_ARGS(_${base}${ctx}_auto${v}_${autoArgcOffset}lessThan_, (flags)$extraFlags, (kind), (keys), (label), ## __VA_ARGS__)>, "";


	push @objcOn, qq<#P#define ${base}${ctx}_auto_rvalue$v(flags, kind, keys, label, value) \a ({ \\
        __typeof__(value) __lpValueTmp = (value); \\
        id __lpMsg = LOGPOINT_FORMAT_VALUE(__lpValueTmp, kLogPointLabelNone); \\
        LOGPOINT_CREATE( (flags)$extraFlags, (kind), (keys), (label), $langSpec, #value, "%@", __lpMsg ); \\
        __lpValueTmp; })>, "";

	push @objcOff, qq<#P#define ${base}${ctx}_auto_rvalue$v(flags, kind, keys, label, value) \a (value)>, "";


	push @objcOn, qq<#P#define ${base}${ctx}_auto_return$v(flags, kind, keys, label, value) \a return ${base}${ctx}_auto_rvalue$v( (flags), (kind), (keys), (label), (value) )>, "";
	push @objcOff, qq<#P#define ${base}${ctx}_auto_return$v(value) \a return (value)>, "";

	for( @objcOnOff ) {
	    push @objcOn, $_;
	    my( $macro, $substitution ) = split(/ *\a */, $_);
	    push @objcOff, length($substitution || '') ? "$macro \a $zero" : defined($macro) ? $macro : '';
	}

	for( @cOnOff ) {
	    push @cOn, $_;
	    my( $macro, $substitution ) = split(/ *\a */, $_);
	    push @cOff, length($substitution || '') ? "$macro \a $zero" : defined($macro) ? $macro : '';
	}


	for( my $i = 0 ; $i <= $count ; ++$i ) {

	    #my $args = $i ? join(", ", map { "l$_, v$_" } 1 .. $i ) : "";
	    my $inArgs = $i ? join(", ", "", map { "v$_" } 1 .. $i ) : "";
	    #my $outargs = $i ? join(", ", map { ( "#v$_", "(v$_)" ) } 1 .. $i ) : "";
	    my $formatInfo = $i ? join(' ", " ', map { "#v$_" } 1 .. $i ) : "kLogPointFormatInfoNone";
	    my $format = $i ? '"'.join(" | ", map { '%@' } 1 .. $i ).'"' : "kLogPointFormatNone";
	    my $parameters = $i ? join(", ", "", map { qq< \\\n\t\t\tLOGPOINT_FORMAT_VALUE( (v$_), #v$_ )> } 1 .. $i ) : "";
	    	    
	    # push @private, sprintf qq<#define _${base}${ctx}_auto${v}_oneLessThan%-2d \a _${base}${ctx}_auto${v}_%-2d>, $_+1, $_ for ( 0 .. $count );
	    
	    my $argc = $i + $autoArgcOffset;

	    push @private, qq<#define _${base}${ctx}_auto${v}_${autoArgcOffset}lessThan_${argc}(flags, kind, keys, label$inArgs) \a LOGPOINT_CREATE((flags)$extraFlags, (kind), (keys), (label), $langSpec, $formatInfo, $format$parameters)>;
	    
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

    push @c, "", "/* used by varargs voodoo in ER_VARARGS_TO_NONZERO_ARGS */", "";

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

    $code =~ s/\n{2,}/\n\n/g;

    return $code;
}


sub output {
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

    if ( $api_macros ) {
	$name = "api_macros";

	push @payload, "", api_macros( count => $count, kind => 'log' ), "";

    }

    if ( $default_macros ) {
	$name = "default_macros";

	push @payload, "", qq<#include "logpoints_api_macros.h">, "";

	for my $kind ( split(/\s*,\s*|\s/, $kinds) ) {
	    push @payload, "", "/* $kind macros */", "", default_macros( count => $count, kind => $kind ), "";
	}
    }

    my $public  = $prefix . '_' . $name . '.h';

    output( $path, $public, map { s/#P#/#/; $_ } @payload );

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

