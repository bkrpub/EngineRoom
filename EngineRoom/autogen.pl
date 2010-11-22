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

    my @cOn = ();
    my @cOff = ();
    my @cOnOff = ();
    my @objcOn = ();
    my @objcOff = ();
    my @objcOnOff = ();

    my $v = 2;

    push @cOnOff, qq<#define ${keyedPrefixKindF}(keys, fmt, ...) \a LOGPOINT_METHOD_OBJC$v($kindFlags, $kindConstant, (keys), kLogPointLabelNone, kLogPointFormatInfoNone, (fmt), ## __VA_ARGS__)>;
    push @cOnOff, qq<#define ${keyedCPrefixKindF}(keys, fmt, ...) \a LOGPOINT_FUNCTION_C$v($kindFlags, $kindConstant, (keys), kLogPointLabelNone, kLogPointFormatInfoNone, (fmt), ## __VA_ARGS__)>;
    push @cOnOff, "";

    my @tmpMeth = ();
    my @tmpFunc = ();

    for( my $i = 0 ; $i < $count ; ++$i ) {

	my $inargs = ($i ? ", " : "" ) . join(", ", map { "v$_" } 1 .. $i );
	my $outargs = ($i ? ", " : "" ) . join(", ", map { ( "#v$_", "(v$_)" ) } 1 .. $i );

	push @tmpMeth, qq<#define $keyedPrefixKind$i(keys$inargs) \a LOGPOINT_METHOD_OBJC_AUTO_VALUE$i($kindFlags, $kindConstant, (keys), kLogPointLabelNone$outargs )>;
	push @tmpFunc, qq<#define $keyedCPrefixKind$i(keys$inargs) \a LOGPOINT_FUNCTION_C_AUTO_VALUE$i($kindFlags, $kindConstant, (keys), kLogPointLabelNone$outargs )>;
    }

    push @objcOnOff, @tmpMeth, "", @tmpFunc, "";

    push @objcOnOff, qq<#define $keyedPrefixKindN(keys, ...) \a ER_VARARGS_TO_NONZERO_ARGS(${keyedPrefixKind}OneLessThan, (keys), ## __VA_ARGS__)>;
    push @objcOnOff, qq<#define $keyedCPrefixKindN(keys, ...) \a ER_VARARGS_TO_NONZERO_ARGS(${keyedCPrefixKind}OneLessThan, (keys), ## __VA_ARGS__)>;
    push @objcOnOff, "";


    push @objcOn, qq<#define $keyedPrefixKindX(keys, value) \a LOGPOINT_METHOD_OBJC_AUTO_EXPR( $kindFlags, $kindConstant, (keys), kLogPointLabelNone, #value, (value))>;
    push @objcOn, qq<#define $keyedCPrefixKindX(keys, value) \a LOGPOINT_FUNCTION_C_AUTO_EXPR( $kindFlags, $kindConstant, (keys), kLogPointLabelNone, #value, (value))>;
    push @objcOn, "";

    push @objcOff, qq<#define $keyedPrefixKindX(value) \a (value)>;
    push @objcOff, qq<#define $keyedCPrefixKindX(value) \a (value)>;
    push @objcOff, "";

    push @objcOn, qq<#define $keyedPrefixKindR(keys, value) \a return LOGPOINT_METHOD_OBJC_AUTO_EXPR( $kindFlags, $kindConstant, (keys), "return", #value, (value))>;
    push @objcOn, qq<#define $keyedCPrefixKindR(keys, value) \a return LOGPOINT_FUNCTION_C_AUTO_EXPR( $kindFlags, $kindConstant, (keys), "return", #value, (value))>;
    push @objcOn, "";

    push @objcOff, qq<#define $keyedPrefixKindR(value) \a return (value)>;
    push @objcOff, qq<#define $keyedCPrefixKindR(value) \a return (value)>;
    push @objcOff, "";

    for( @objcOnOff ) {
	my( $macro, $substitution ) = split(/ *\a */, $_);
	push @objcOn, $_;
	push @objcOff, length($substitution) ? "$macro \a $zero" : $macro;
    }

    for( @cOnOff ) {
	my( $macro, $substitution ) = split(/ *\a */, $_);
	push @cOn, $_;
	push @cOff, length($substitution) ? "$macro \a $zero" : $macro;
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

    push @c, sprintf qq<#define ${keyedPrefixKind}OneLessThan%-2d \a ${keyedPrefixKind}%-2d>, $_+1, $_ for ( 0 .. $count );

    push @c, sprintf qq<#define ${keyedCPrefixKind}OneLessThan%-2d \a ${keyedCPrefixKind}%-2d>, $_+1, $_ for ( 0 .. $count );

    push @c, "", "/* non-keyed variants */";

    push @c, qq<#define $prefixKindF(fmt, ...) \a $keyedPrefixKindF(kLogPointKeysNone, (fmt), ## __VA_ARGS__)>;
    push @c, qq<#define $cPrefixKindF(fmt, ...) \a $keyedCPrefixKindF(kLogPointKeysNone, (fmt), ## __VA_ARGS__)>;
    push @c, qq<#define $prefixKindN(...) \a $keyedPrefixKindN(kLogPointKeysNone, ## __VA_ARGS__)>;
    push @c, qq<#define $cPrefixKindN(...) \a $keyedCPrefixKindN(kLogPointKeysNone, ## __VA_ARGS__)>;
    push @c, qq<#define $prefixKindX(value) \a $keyedPrefixKindX(kLogPointKeysNone, value)>;
    push @c, qq<#define $cPrefixKindX(value) \a $keyedCPrefixKindX(kLogPointKeysNone, value)>;
    push @c, qq<#define $prefixKindR(value) \a $keyedPrefixKindR(kLogPointKeysNone, value)>;
    push @c, qq<#define $cPrefixKindR(value) \a $keyedCPrefixKindR(kLogPointKeysNone, value)>;


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
	@rest ? sprintf("%-*s%s%s", $maxLength, $macro, 
			$sep,
			join($sep, @rest)) : $macro;
			    } @c), "");

    $code =~ s/\n{2,}/\n\n/g;

    return $code;
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
	for my $kind ( qw( trace debug info notice warning error ) ) {
	    push @payload, "", "/* $kind macros */", "", template( count => $count, kind => $kind ), "";
	}
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

