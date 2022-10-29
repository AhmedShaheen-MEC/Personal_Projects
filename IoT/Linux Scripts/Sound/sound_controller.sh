#!/bin/bash

command=$1

analog_id=49
hdmi_id=0
combined=1 

# Last ID, combined stream ID, save to file
input_sinks_id=( `pactl list short sink-inputs | awk '{  print $1;  }' `)
input_sinks_indicator=( `pactl list short sink-inputs | awk '{  print $3;  }' `)
#echo ${input_sinks_indicator[-2]}
#echo ${input_sinks_indicator[-1]}
main_stream_indicator=`cat main_stream`
mic_stream_ind=`cat mic_stream`
echo Saved Streams $main_stream_indicator $mic_stream_ind
main_stream_id=0
mic_id=0
counter=0
for id in "${input_sinks_indicator[@]}"; do
	echo ID is: $id
	if [ "$id" -eq "${main_stream_indicator}" ]; then
		main_stream_id=${input_sinks_id[(( counter ))]}
	elif [ "$id" -eq "$mic_stream_ind" ]; then
		mic_id=${input_sinks_id[(( counter ))]}
	fi

	let "counter +=1"
done
echo Main Stream ID:  $main_stream_id
echo MIC Stream ID: $mic_id
#len=`echo ${input_sinks_id} | awk '{ print length; }'`
#echo  Number of streams: $counter

#if (( $counter == 1 )); then
#	echo Single Stream with ID: ${input_sinks_id[0]}
#	echo ${input_sinks_id[0]} >> original_id
#else 
echo Command ${command}
if [ "${command}" ==  "m" ]; then
	echo Merging MAIN stream to Single stream
	pactl move-sink-input ${main_stream_id} ${combined}
else 
	echo Separating The Two streams
	pactl move-sink-input ${main_stream_id} ${hdmi_id}
	pactl move-sink-input ${mic_id} ${analog_id}
fi
