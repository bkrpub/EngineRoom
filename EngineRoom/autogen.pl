#!/usr/bin/env perl -s 

our $path = "generated";

our $prefix ||= "logpoints";
our $name ||= "custom";
our $kind ||= "debug";
our $count ||= 3;

our $auto_value ||= 0;

sub auto_value( $ ) {

    my $count = shift;

    my @macros = ();

    my $args = '';
    my $format = '';
    my $formatInfo = '';
    my $param = '';

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

	    my $substitution  = qq<\t\tLOGPOINT_${style}2( (flags), (kind), (keys), (label), $formatInfo,  "$format", $parameters )\n>;

	    if( 0 == $i ) {
		$substitution = qq<\t\tLOGPOINT_${style}2( (flags), (kind), (keys), (label), kLogPointFormatInfoNone, kLogPointFormatNone )\n>;
	    }

	    my $macro = qq<#define LOGPOINT_${style}_AUTO_VALUE$i(flags, kind, keys, label> . (length($args) ? ", $args" : "") . qq<) \t \\\n$substitution\n>;
	    
	    push @macros, $macro;

	}
    }

    return @macros;
}

sub template( % ) {
    my %p = @_;

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

    my $kindConstant = ${kindConstant} || "kLogPointKind${ucFirstKind}";

    my $prefixKind = "$prefix$lcKind";
    my $cPrefixKind = "$cPrefix$lcKind";

    my $keyedPrefixKind = "$keyedPrefix$lcKind";
    my $keyedCPrefixKind = "$keyedCPrefix$lcKind";

    my $prefixKindF = $p{prefixKindF} || "${prefixKind}f"; 
    my $cPrefixKindF = $p{cPrefixKindF} || "${cPrefixKind}f"; 

    my $keyedPrefixKindF = $p{keyedPrefixKindF} || "${keyedPrefixKind}f"; 
    my $keyedCPrefixKindF = $p{keyedCPrefixKindF} || "${keyedCPrefixKind}f"; 

    my $prefixKindN = $p{prefixKindN} || "${prefixKind}n"; 
    my $cPrefixKindN = $p{cPrefixKindN} || "${cPrefixKind}n"; 

    my $keyedPrefixKindN = $p{keyedPrefixKindN} || "${keyedPrefixKind}n"; 
    my $keyedCPrefixKindN = $p{keyedCPrefixKindN} || "${keyedCPrefixKind}n"; 

    my $prefixKindX = $p{prefixKindX} || "${prefixKind}_expr"; 
    my $cPrefixKindX = $p{cPrefixKindX} || "${cPrefixKind}_expr"; 

    my $keyedPrefixKindX = $p{keyedPrefixKindX} || "${keyedPrefixKind}_expr"; 
    my $keyedCPrefixKindX = $p{keyedCPrefixKindX} || "${keyedCPrefixKind}_expr"; 

    my $prefixKindR = $p{prefixKindR} || "${prefixKind}_return"; 
    my $cPrefixKindR = $p{cPrefixKindR} || "${cPrefixKind}_return"; 

    my $keyedPrefixKindR = $p{keyedPrefixKindR} || "${keyedPrefixKind}_return"; 
    my $keyedCPrefixKindR = $p{keyedCPrefixKindR} || "${keyedCPrefixKind}_return"; 

    my @c = ();
    my @e = (); # code to duplicate as zero macro if not enabled

    my $v = 2;

    push @c, sprintf qq<#define ${keyedPrefixKind}OneLessThan%-2d \t ${keyedPrefixKind}%-2d>, $_+1, $_ for ( 0 .. $count );
    push @c, "";

    push @c, sprintf qq<#define ${keyedCPrefixKind}OneLessThan%-2d \t ${keyedCPrefixKind}%-2d>, $_+1, $_ for ( 0 .. $count );

    push @c, "", "#if LOGPOINT_ENABLE_${ucKind}", "";

    push @e, "", "#if __OBJC__", "";


    push @e, qq<#define $keyedPrefixKindN(keys, ...) \t ER_VARARGS_TO_NONZERO_ARGS(${keyedPrefixKind}OneLessThan, (keys), ## __VA_ARGS__)>;
    push @e, qq<#define $keyedCPrefixKindN(keys, ...) \t ER_VARARGS_TO_NONZERO_ARGS(${keyedCPrefixKind}OneLessThan, (keys), ## __VA_ARGS__)>;

    push @e, "";

    push @e, qq<#define $prefixKindN(...) \t $keyedPrefixKindN(kLogPointKeysNone, ## __VA_ARGS__)>;
    push @e, qq<#define $cPrefixKindN(...) \t $keyedCPrefixKindN(kLogPointKeysNone, ## __VA_ARGS__)>;

    push @e, "";

    my @_objc = ();
    my @_c = ();



    for( my $i = 0 ; $i < $count ; ++$i ) {

	my $inargs = ($i ? ", " : "" ) . join(", ", map { "v$_" } 1 .. $i );
	my $outargs = ($i ? ", " : "" ) . join(", ", map { ( "#v$_", "(v$_)" ) } 1 .. $i );

	push @_objc, qq<#define $keyedPrefixKind$i(keys$inargs) \t LOGPOINT_METHOD_OBJC_AUTO_VALUE$i($kindFlags, $kindConstant, (keys), kLogPointLabelNone$outargs )>;
	push @_c,    qq<#define $keyedCPrefixKind$i(keys$inargs) \t LOGPOINT_FUNCTION_C_AUTO_VALUE$i($kindFlags, $kindConstant, (keys), kLogPointLabelNone$outargs )>;
    }

    push @e, @_objc, "", @_c;

    push @e, "", "#endif\n/* __OBJC__ */", "";


    push @e, qq<#define ${keyedPrefixKindF}(keys, fmt, ...) \t LOGPOINT_METHOD_OBJC$v($kindFlags, $kindConstant, (keys), kLogPointLabelNone, kLogPointFormatInfoNone, (fmt), ## __VA_ARGS__)>;
    push @e, qq<#define ${keyedCPrefixKindF}(keys, fmt, ...) \t LOGPOINT_FUNCTION_C$v($kindFlags, $kindConstant, (keys), kLogPointLabelNone, kLogPointFormatInfoNone, (fmt), ## __VA_ARGS__)>;

    push @e, "";

    push @e, qq<#define $prefixKindF(fmt, ...) \t $keyedPrefixKindF(kLogPointKeysNone, (fmt), ## __VA_ARGS__)>;
    push @e, qq<#define $cPrefixKindF(fmt, ...) \t $keyedCPrefixKindF(kLogPointKeysNone, (fmt), ## __VA_ARGS__)>;

    # end e

    push @c, @e;

    push @c, qq<#define $prefixKindX(value) \t LOGPOINT_METHOD_OBJC_AUTO_EXPR( $kindFlags, $kindConstant, kLogPointKeysNone, kLogPointLabelNone, #value, (value))>;
    push @c, qq<#define $cPrefixKindX(value) \t LOGPOINT_FUNCTION_C_AUTO_EXPR( $kindFlags, $kindConstant, kLogPointKeysNone, kLogPointLabelNone, #value, (value))>;

    push @c, "";

    push @c, qq<#define $prefixKindR(value) \t return LOGPOINT_METHOD_OBJC_AUTO_EXPR( $kindFlags, $kindConstant, kLogPointKeysNone, "return", #value, (value))>;
    push @c, qq<#define $cPrefixKindR(value) \t return LOGPOINT_FUNCTION_C_AUTO_EXPR( $kindFlags, $kindConstant, kLogPointKeysNone, "return", #value, (value))>;

    push @c, "";

    push @c, "", "#else", "/* ! LOGPOINT_ENABLE_${ucKind} */", "";

    for( @e ) {
	my( $macro, $substitution ) = split(/ *\t */, $_);
	push @c, length($substitution) ? "$macro \t $zero" : $macro;
    }

    push @c, "";

    push @c, qq<#define $prefixKindX(value) \t (value)>;
    push @c, qq<#define $cPrefixKindX(value) \t (value)>;

    push @c, "";

    push @c, qq<#define $prefixKindR(value) \t return (value)>;
    push @c, qq<#define $cPrefixKindR(value) \t return (value)>;

    push @c, "", "#endif", "/* LOGPOINT_ENABLE_${ucKind} */", "";

    return @c;
}


sub beautify ( @ ) {
    my @c = @_;
    my(@macros) = ();
    my(@substitutions) = ();
    my $maxLength = 0;

    for( @c ){
	my( $macro, @rest ) = split(/ *\t */, $_);

	next unless @rest;

	$maxLength = length($macro) if length($macro) > $maxLength;
    }

    return join("\n", "", ( map {
	my( $macro, @rest ) = split(/ *\t */, $_);

	@rest ? sprintf("%-*s\t%s", $maxLength, $macro, join("\t", @rest)) : $macro;
	    } @c), "");

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
	push @payload, template( count => $count, kind => $kind );
    }


    my $file = $prefix . '_' . $name . '.h';
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

