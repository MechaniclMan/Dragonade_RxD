package DA;

use plugin;
use POE;

our $plugin_name;
our %config;
our $currentVersion = 1.0;

our %additional_events = (
	"PlayerKill" => "PlayerKill",
	"BotKill" => "BotKill",
	"VehKill" => "VehKill",
	"HarvKill" => "HarvKill",
	"BuildingKill" => "BuildingKill",
	"Building" => "Building",
	"Vehicle" => "Vehicle",
	"Purchase" => "Purchase",
	"C4" => "C4",
	"ConnectionRefused" => "ConnectionRefused",
	"Ban" => "Ban",
	"Cheat" => "Cheat",
	"Error" => "Error",
	"Alert" => "Alert",
	"Node" => "Node",
	"Flag" => "Flag",
	"Squad" => "Squad",
);

sub GetColor {
	my $p = shift;
	my $color = "";
	if ($p eq "Nod" || $p eq "0") { 
		$color = "04"; 
	}
	elsif ($p eq "GDI" || $p eq "1") { 
		$color = "08"; 
	}
	return $color;
}

sub PlayerKill {
	my ( $kernel, $session, $heap, $args ) = @_[ KERNEL, SESSION, HEAP, ARG0 ];
	my %args = %{$args};
	my $line = $args->{'line'};
	if ($line =~ /^\[\d\d:\d\d:\d\d\]\s_PLAYERKILL\s(\d)\s(.+)$/) {
		my $color = GetColor($1);
		plugin::ircmsg("07[KILL]$color $2","");
	}
}

sub BotKill {
	my ( $kernel, $session, $heap, $args ) = @_[ KERNEL, SESSION, HEAP, ARG0 ];
	my %args = %{$args};
	my $line = $args->{'line'};
	if ($line =~ /^\[\d\d:\d\d:\d\d\]\s_BOTKILL\s(\d)\s(.+)$/) {
		my $color = GetColor($1);
		plugin::ircmsg("07[BOTKILL]$color $2","");
	}
}

sub VehKill {
	my ( $kernel, $session, $heap, $args ) = @_[ KERNEL, SESSION, HEAP, ARG0 ];
	my %args = %{$args};
	my $line = $args->{'line'};
	if ($line =~ /^\[\d\d:\d\d:\d\d\]\s_VEHKILL\s(\d)\s(.+)$/) {
		my $color = GetColor($1);
		plugin::ircmsg("07[VEHKILL]$color $2","");
	}
}

sub HarvKill {
	my ( $kernel, $session, $heap, $args ) = @_[ KERNEL, SESSION, HEAP, ARG0 ];
	my %args = %{$args};
	my $line = $args->{'line'};
	if ($line =~ /^\[\d\d:\d\d:\d\d\]\s_HARVKILL\s(\d)\s(.+)$/) {
		my $color = GetColor($1);
		plugin::ircmsg("07[HARVKILL]$color $2","");
	}
}

sub BuildingKill {
	my ( $kernel, $session, $heap, $args ) = @_[ KERNEL, SESSION, HEAP, ARG0 ];
	my %args = %{$args};
	my $line = $args->{'line'};
	if ($line =~ /^\[\d\d:\d\d:\d\d\]\s_BUILDINGKILL\s(\d)\s(.+)$/) {
		my $color = GetColor($1);
		plugin::ircmsg("07[BUILDINGKILL]$color $2","");
	}
}

sub Building {
	my ( $kernel, $session, $heap, $args ) = @_[ KERNEL, SESSION, HEAP, ARG0 ];
	my %args = %{$args};
	my $line = $args->{'line'};
	if ($line =~ /^\[\d\d:\d\d:\d\d\]\s_BUILDING\s(\w+)\s(.+)$/) {
		my $color = GetColor($1);
		plugin::ircmsg("03[BUILDING]$color $1 $2","");
	}
}

sub Vehicle {
	my ( $kernel, $session, $heap, $args ) = @_[ KERNEL, SESSION, HEAP, ARG0 ];
	my %args = %{$args};
	my $line = $args->{'line'};
	if ($line =~ /^\[\d\d:\d\d:\d\d\]\s_VEHICLE\s(\d)\s(.+)$/) {
		my $color = GetColor($1);
		plugin::ircmsg("03[VEHICLE]$color $2","");
	}
}

sub Purchase {
	my ( $kernel, $session, $heap, $args ) = @_[ KERNEL, SESSION, HEAP, ARG0 ];
	my %args = %{$args};
	my $line = $args->{'line'};
	if ($line =~ /^\[\d\d:\d\d:\d\d\]\s_PURCHASE\s(.+)$/) {
		plugin::ircmsg("03[PURCHASE] $1","A");
	}
}

sub C4 {
	my ( $kernel, $session, $heap, $args ) = @_[ KERNEL, SESSION, HEAP, ARG0 ];
	my %args = %{$args};
	my $line = $args->{'line'};
	if ($line =~ /^\[\d\d:\d\d:\d\d\]\s_C4\s(.+)$/) {
		plugin::ircmsg("03[C4] $1","A");
	}
}

sub ConnectionRefused {
	my ( $kernel, $session, $heap, $args ) = @_[ KERNEL, SESSION, HEAP, ARG0 ];
	my %args = %{$args};
	my $line = $args->{'line'};
	if ($line =~ /^\[\d\d:\d\d:\d\d\]\s_CONNECTIONREFUSED\s(.+)$/) {
		plugin::ircmsg("04[CONNECTIONREFUSED] $1","A");
	}
}

sub Ban {
	my ( $kernel, $session, $heap, $args ) = @_[ KERNEL, SESSION, HEAP, ARG0 ];
	my %args = %{$args};
	my $line = $args->{'line'};
	if ($line =~ /^\[\d\d:\d\d:\d\d\]\s_BAN\s(.+)$/) {
		plugin::ircmsg("04[BAN] $1","A");
	}
}

sub Cheat {
	my ( $kernel, $session, $heap, $args ) = @_[ KERNEL, SESSION, HEAP, ARG0 ];
	my %args = %{$args};
	my $line = $args->{'line'};
	if ($line =~ /^\[\d\d:\d\d:\d\d\]\s_CHEAT\s(.+)$/) {
		plugin::ircmsg("04[CHEAT] $1","A");
	}
}

sub Error {
	my ( $kernel, $session, $heap, $args ) = @_[ KERNEL, SESSION, HEAP, ARG0 ];
	my %args = %{$args};
	my $line = $args->{'line'};
	if ($line =~ /^\[\d\d:\d\d:\d\d\]\s_ERROR\s(.+)$/) {
		plugin::ircmsg("04[ERROR] $1","A");
	}
}

sub Alert {
	my ( $kernel, $session, $heap, $args ) = @_[ KERNEL, SESSION, HEAP, ARG0 ];
	my %args = %{$args};
	my $line = $args->{'line'};
	if ($line =~ /^\[\d\d:\d\d:\d\d\]\s_ALERT\s(.+)$/) {
		plugin::ircmsg("04[ALERT] $1","A");
	}
}

sub Node {
	my ( $kernel, $session, $heap, $args ) = @_[ KERNEL, SESSION, HEAP, ARG0 ];
	my %args = %{$args};
	my $line = $args->{'line'};
	if ($line =~ /^\[\d\d:\d\d:\d\d\]\s_NODE\s(\d)\s(.+)$/) {
		my $color = GetColor($1);
		plugin::ircmsg("09[NODE]$color $2","");
	}
}

sub Flag {
	my ( $kernel, $session, $heap, $args ) = @_[ KERNEL, SESSION, HEAP, ARG0 ];
	my %args = %{$args};
	my $line = $args->{'line'};
	if ($line =~ /^\[\d\d:\d\d:\d\d\]\s_FLAG\s(\d)\s(.+)$/) {
		my $color = GetColor($1);
		plugin::ircmsg("09[FLAG]$color $2","");
	}
}

sub Squad {
	my ( $kernel, $session, $heap, $args ) = @_[ KERNEL, SESSION, HEAP, ARG0 ];
	my %args = %{$args};
	my $line = $args->{'line'};
	if ($line =~ /^\[\d\d:\d\d:\d\d\]\s_SQUAD\s(.+)$/) {
		plugin::ircmsg("03[SQUAD] $1","");
	}
}

sub start {
	my ( $kernel, $session, $heap, $args ) = @_[ KERNEL, SESSION, HEAP, ARG0 ];
	print "Dragonade Log Plugin loaded.\n";
	return 1;
}

sub stop {
	my ( $kernel, $session, $heap, $args ) = @_[ KERNEL, SESSION, HEAP, ARG0 ];
	print "Dragonade Log Plugin unloaded.\n";
	return 1;
}

1;