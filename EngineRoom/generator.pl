#!/usr/bin/env perl -s 

our $path = "generated";

our $prefix ||= "logpoints";
our $name ||= "custom";
our $count ||= 20;

our $auto_value ||= 0;

sub auto_value( $ ) {

    my $count = shift;

    my @macros = ();

    my $args = '';
    my $format = '';
    my $formatInfo = '';
    my $param = '';

    for( my $i = 1 ; $i <= $count ; ++$i ) {

	$args .= ", " if $args;
	$args .= "l$i, v$i";
	
	$formatInfo .= qq( ", " ) if $formatInfo;
	$formatInfo .= qq(l$i);

	$format .= ' | ' if $format;
	$format .= '%@';

	$parameters .= ', ' if $parameters;
	$parameters .= qq< \\\n\t\t\tLOGPOINT_FORMAT_VALUE( (v$i), (l$i) )>;

	for my $style ( qw( METHOD_OBJC FUNCTION_C ) ) {

	    my $substitution = qq<\t\tLOGPOINT_${style}2( (flags), (kind), (keys), (label), $formatInfo,  "$format", $parameters \\\n\t\t)\n>;
	    
	    my $macro = qq<#define LOGPOINT_${style}_AUTO_VALUE$i(flags, kind, keys, label, $args) \\\n$substitution\n>;
	    
	    push @macros, $macro;

	}
    }

    return @macros;
}

sub main() {

    my @content = ();
    my @payload = ();

    if ( $auto_value ) {
	$name = "auto_value";
	push @payload, auto_value($count);
    }

    my $file = $prefix . '_' . $name . '.h';
    my $marker = $file;
    $marker =~ s/\./_/g;
    $marker = '__' . uc($marker) . '__';
    
    push @content, "/*\n * $file - generated code\n */\n\n";

    push @content, "#ifndef $marker\n#define $marker 1\n\n";

    push @content, @payload;

    push @content, "\n#endif\n /* $marker */\n";

    my $output = "$path/$file";
    open(FILE, ">", $output) or die "can't open $output for writing ($!)\n";
    print FILE @content;
    close(FILE);

    return 0;
}

exit &main;
