#!/usr/bin/env perl -s 

use strict;
use warnings;

our $path = "generated";

our $prefix ||= "logpoints";
our $name ||= "custom";
our $kinds ||= "switch assert debug info notice warning error";
our $count ||= 16;

our $auto_value ||= 0;
our $template ||= 0;

sub auto_value( $ ) {

    my $count = shift;

    my @macros = ();

    my $args = '';
    my $format = '';
    my $formatInfo = '';
    my $parameters = '';

    for( my $i = 0 ; $i <= $count ; ++$i ) {

	if( $i ) {
	    $args .= ", " if $args;
	    $args .= "l$i, v$i";
	    
	    $formatInfo .= qq( ", " ) if $formatInfo;
	    $formatInfo .= qq(l$i);
	    
	    $format .= ' | ' if $format;
	    $format .= '%@';
	    
	    $parameters .= ', ' if $parameters;
	    $parameters .= qq< \\\n\t\t\tLOGPOINT_FORMAT_VALUE( (v$i), (l$i) )>;
	}

	for my $style ( qw( METHOD_OBJC FUNCTION_C ) ) {

	    my $substitution  = qq<\t\tLOGPOINT_${style}( (flags), (kind), (keys), (label), $formatInfo,  "$format", $parameters )\n>;

	    if( 0 == $i ) {
		$substitution = qq<\t\tLOGPOINT_${style}( (flags), (kind), (keys), (label), kLogPointFormatInfoNone, kLogPointFormatNone )\n>;
	    }

	    my $macro = qq<#define LOGPOINT_${style}_AUTO_VALUE$i(flags, kind, keys, label> . (length($args) ? ", $args" : "") . qq<) \\\a\n$substitution>;
	    
	    push @macros, $macro;

	}

	push @macros, "";
    }

    return @macros;
}

sub template( % ) {
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

    my $prefixKindF = $p{prefixKindF} || "${prefixKind}F"; 
    my $cPrefixKindF = $p{cPrefixKindF} || "${cPrefixKind}F"; 

    my $keyedPrefixKindF = $p{keyedPrefixKindF} || "${keyedPrefixKind}F"; 
    my $keyedCPrefixKindF = $p{keyedCPrefixKindF} || "${keyedCPrefixKind}F"; 

    my $prefixKindN = $p{prefixKindN} || "${prefixKind}N"; 
    my $cPrefixKindN = $p{cPrefixKindN} || "${cPrefixKind}N"; 

    my $keyedPrefixKindN = $p{keyedPrefixKindN} || "${keyedPrefixKind}N"; 
    my $keyedCPrefixKindN = $p{keyedCPrefixKindN} || "${keyedCPrefixKind}N"; 

    my $prefixKindX = $p{prefixKindX} || "${prefixKind}X"; 
    my $cPrefixKindX = $p{cPrefixKindX} || "${cPrefixKind}X"; 

    my $keyedPrefixKindX = $p{keyedPrefixKindX} || "${keyedPrefixKind}X"; 
    my $keyedCPrefixKindX = $p{keyedCPrefixKindX} || "${keyedCPrefixKind}X"; 

    my $prefixKindR = $p{prefixKindR} || "${prefixKind}R"; 
    my $cPrefixKindR = $p{cPrefixKindR} || "${cPrefixKind}R"; 

    my $keyedPrefixKindR = $p{keyedPrefixKindR} || "${keyedPrefixKind}R"; 
    my $keyedCPrefixKindR = $p{keyedCPrefixKindR} || "${keyedCPrefixKind}R"; 

    my @c = ();

    my @cOn = ();
    my @cOff = ();
    my @cOnOff = ();
    my @objcOn = ();
    my @objcOff = ();
    my @objcOnOff = ();

    my $v = 2;

    push @cOnOff, qq<#P#define _$keyedPrefixKindF(keys, fmt, ...) \a LOGPOINT_METHOD_OBJC$v($kindFlags, $kindConstant, (keys), kLogPointLabelNone, kLogPointFormatInfoNone, (fmt), ## __VA_ARGS__)>;
    push @cOnOff, qq<#P#define _$keyedCPrefixKindF(keys, fmt, ...) \a LOGPOINT_FUNCTION_C$v($kindFlags, $kindConstant, (keys), kLogPointLabelNone, kLogPointFormatInfoNone, (fmt), ## __VA_ARGS__)>;
    push @cOnOff, "";

    my @tmpMeth = ();
    my @tmpFunc = ();

    for( my $i = 0 ; $i < $count ; ++$i ) {

	my $inargs = ($i ? ", " : "" ) . join(", ", map { "v$_" } 1 .. $i );
	my $outargs = ($i ? ", " : "" ) . join(", ", map { ( "#v$_", "(v$_)" ) } 1 .. $i );
	
	my $extraFlags = ($i == 0 && $kind eq 'switch' ) ? ' | LOGPOINT_SILENT' : '';

	my $flags = $kindFlags . $extraFlags;

	push @tmpMeth, qq<#define _$keyedPrefixKind$i(keys$inargs) \a LOGPOINT_METHOD_OBJC_AUTO_VALUE$i($flags, $kindConstant, (keys), kLogPointLabelNone$outargs )>;
	push @tmpFunc, qq<#define _$keyedCPrefixKind$i(keys$inargs) \a LOGPOINT_FUNCTION_C_AUTO_VALUE$i($flags, $kindConstant, (keys), kLogPointLabelNone$outargs )>;
    }

    push @objcOnOff, @tmpMeth, "", @tmpFunc, "";

    push @objcOnOff, qq<#P#define _$keyedPrefixKindN(keys, ...) \a ER_VARARGS_TO_NONZERO_ARGS(${keyedPrefixKind}OneLessThan, (keys), ## __VA_ARGS__)>;
    push @objcOnOff, qq<#P#define _$keyedCPrefixKindN(keys, ...) \a ER_VARARGS_TO_NONZERO_ARGS(${keyedCPrefixKind}OneLessThan, (keys), ## __VA_ARGS__)>;
    push @objcOnOff, "";


    push @objcOn, qq<#P#define _$keyedPrefixKindX(keys, value) \a LOGPOINT_METHOD_OBJC_AUTO_EXPR( $kindFlags, $kindConstant, (keys), kLogPointLabelNone, #value, (value))>;
    push @objcOn, qq<#P#define _$keyedCPrefixKindX(keys, value) \a LOGPOINT_FUNCTION_C_AUTO_EXPR( $kindFlags, $kindConstant, (keys), kLogPointLabelNone, #value, (value))>;
    push @objcOn, "";

    push @objcOff, qq<#define _$keyedPrefixKindX(value) \a (value)>;
    push @objcOff, qq<#define _$keyedCPrefixKindX(value) \a (value)>;
    push @objcOff, "";

    push @objcOn, qq<#P#define _$keyedPrefixKindR(keys, value) \a return LOGPOINT_METHOD_OBJC_AUTO_EXPR( $kindFlags, $kindConstant, (keys), "return", #value, (value))>;
    push @objcOn, qq<#P#define _$keyedCPrefixKindR(keys, value) \a return LOGPOINT_FUNCTION_C_AUTO_EXPR( $kindFlags, $kindConstant, (keys), "return", #value, (value))>;
    push @objcOn, "";

    push @objcOff, qq<#define _$keyedPrefixKindR(value) \a return (value)>;
    push @objcOff, qq<#define _$keyedCPrefixKindR(value) \a return (value)>;
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

    push @c, "", "/* used by varargs voodoo in ER_VARARGS_TO_NONZERO_ARGS */", "";

    push @c, sprintf qq<#define _${keyedPrefixKind}OneLessThan%-2d \a _${keyedPrefixKind}%-2d>, $_+1, $_ for ( 0 .. $count );

    push @c, sprintf qq<#define _${keyedCPrefixKind}OneLessThan%-2d \a _${keyedCPrefixKind}%-2d>, $_+1, $_ for ( 0 .. $count );

    push @c, "", "/* non-keyed variants */";

    push @c, qq<#P#define _$prefixKindF(fmt, ...) \a _$keyedPrefixKindF(kLogPointKeysNone, (fmt), ## __VA_ARGS__)>;
    push @c, qq<#P#define _$cPrefixKindF(fmt, ...) \a _$keyedCPrefixKindF(kLogPointKeysNone, (fmt), ## __VA_ARGS__)>;
    push @c, qq<#P#define _$prefixKindN(...) \a _$keyedPrefixKindN(kLogPointKeysNone, ## __VA_ARGS__)>;
    push @c, qq<#P#define _$cPrefixKindN(...) \a _$keyedCPrefixKindN(kLogPointKeysNone, ## __VA_ARGS__)>;
    push @c, qq<#P#define _$prefixKindX(value) \a _$keyedPrefixKindX(kLogPointKeysNone, value)>;
    push @c, qq<#P#define _$cPrefixKindX(value) \a _$keyedCPrefixKindX(kLogPointKeysNone, value)>;
    push @c, qq<#P#define _$prefixKindR(value) \a _$keyedPrefixKindR(kLogPointKeysNone, value)>;
    push @c, qq<#P#define _$cPrefixKindR(value) \a _$keyedCPrefixKindR(kLogPointKeysNone, value)>;

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


sub private {
    my @out = @_;

    s/^#P#/#/ for @out;

    return @out;
}

sub public {
    my @in = @_;
    my @out = ();

    my $lastWasPublic = 0;

    for ( @in ) {

	if( m/#P#define\s+(\w+).*?\a.*/m ) {
	    my $private = $1;
	    my $public = $1;
	    $public =~ s/^_//;

# mapping
	    $public =~ s/N$//;
	    $public =~ s/F$/f/;
	    $public =~ s/X$/_expr/;
	    $public =~ s/R$/_return/;

# lpkswitchf("foo bar", "some %s here", "baz") # verbose
# lpkswitch("foo bar") # silent
# lpkswitch("foo bar", myrect) # verbose -> n
# lpswitchf("some %s here", "baz") # verbose 
# lpswitch() # silent
# lpswitch("foo") # verbose

# /mapping


	    $_ = "#define $public \a $private";
	    
	    $lastWasPublic = 1;

	    push @out, $_;
	} else {
	    # copy empty lines trailing public defs
	    if( $lastWasPublic ) {
		push @out, $_ if 0 == length $_; 
		$lastWasPublic = 0;
	    }
	}
    }

    return @out;
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

    if ( $auto_value ) {
	$name = "auto_value";
	push @payload, auto_value($count);
    }

    if ( $template ) {
	$name = "template";

	push @payload, auto_value($count);

	for my $kind ( split(/\s*,\s*|\s/, $kinds) ) {
	    push @payload, "", "/* $kind macros */", "", template( count => $count, kind => $kind ), "";
	}
    }

    my $private = $prefix . '_' . $name . '_private.h';
    my $public  = $prefix . '_' . $name . '.h';

    output( $path, $private, private( @payload ) );
    output( $path, $public, public( @payload ) );

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

