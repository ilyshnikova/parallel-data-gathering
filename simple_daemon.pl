#!/usr/bin/perl

use strict;
use warnings;
use IO::Socket::INET;

my $port = shift;

my $socket = new IO::Socket::INET (
    LocalPort => $port,
    Proto => 'tcp',
    Listen => 1,
    Reuse => 1
) or die "Oops: $! \n";
print "Waiting for the Client.\n";


while (my $clientsocket = $socket->accept()){
	print   "Connected from : ", $clientsocket->peerhost();     # Display messages
	print   ", Port : ", $clientsocket->peerport(), "\n";

	print "Time of client message: " . time() . "\n";
	sleep(2);
	print "Time of response: " . time() . "\n";

	print $clientsocket "Currency is now 12342.23487\n\r\n";


	$clientsocket->close();
}
