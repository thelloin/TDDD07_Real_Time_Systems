/**
 * @file	task_communicate.c
 * @author  Eriks Zaharans
 * @date    31 Oct 2013
 *
 * @section DESCRIPTION
 *
 * Communicate Task.
 */

/* -- Includes -- */
/* system libraries */

/* project libraries */
#include "task.h"
#include <stdio.h>

/**
 * Communication (receive and send data)
 */
void task_communicate(void)
{
  // Check if task is enabled
  if(g_task_communicate.enabled == s_TRUE)
  {
    // Loacal variables
    void *data; // Void pointer for data
    int data_type; // Data type

    // UDP Packet
    char udp_packet[g_config.udp_packet_size];
    int udp_packet_len;

    // Protocol
    protocol_t packet;

    //Start the new sequence
    int seq = 0; // Massi thing
    //In principle I want to send all the data in the buffer
    int last_id = g_list_send->count; // Massi thing
    //printf("we are here -1");
    doublylinkedlist_t *robot_list = doublylinkedlist_init();
    doublylinkedlist_t *victim_list = doublylinkedlist_init();
    doublylinkedlist_t *pheromone_list = doublylinkedlist_init();
    doublylinkedlist_t *stream_list = doublylinkedlist_init();
    doublylinkedlist_t **list_to_insert;
		

    // --------------------------------------------------
    //	LAB 2 starts here
    // --------------------------------------------------
    int bytes_sent = 0;

    /* --- Send Data --- */
    while(g_list_send->count != 0)
    {
      seq++;

      // Allocate memory for data structure
      switch(g_list_send->first->data_type)
      {
	// Robot pose
	case s_DATA_STRUCT_TYPE_ROBOT :
	  data = (void *)malloc(sizeof(robot_t));
	  list_to_insert = &robot_list;
	  break;
	  // Victim information
	case s_DATA_STRUCT_TYPE_VICTIM :
	  data = (void *)malloc(sizeof(victim_t));
	  list_to_insert = &victim_list;
	  break;
	  // Pheromone map
	case s_DATA_STRUCT_TYPE_PHEROMONE :
	  data = (void *)malloc(sizeof(pheromone_map_sector_t));
	  list_to_insert = &pheromone_list;
	  break;
	  // Command (for future use)
	case s_DATA_STRUCT_TYPE_CMD :
	  data = (void *)malloc(sizeof(command_t));
	  break;
	case s_DATA_STRUCT_TYPE_STREAM :
	  data = (void *)malloc(sizeof(stream_t));
	  list_to_insert = &stream_list;
	  break;
	  // Other
	default :
	  // Do nothing
	  continue;
	  break;
      }

      // Get data from the list
      doublylinkedlist_remove(g_list_send, g_list_send->first ,data, &data_type);
      //printf("PHERMONE TYPE: %d \n", s_DATA_STRUCT_TYPE_PHEROMONE);
      //printf("DATA_TYPE: %d      DATA STRUCT_TYPE: %d \n", data_type, s_DATA_STRUCT_TYPE_STREAM);
      //Insert data into respective list **ours**
      if(data_type == s_DATA_STRUCT_TYPE_STREAM) {
	
	doublylinkedlist_insert_beginning(*list_to_insert, data, data_type);
      } else if (data_type == s_DATA_STRUCT_TYPE_PHEROMONE) {
	doublylinkedlist_insert_beginning(*list_to_insert, data, data_type);
      } else {
	// Encode data into UDP packet
	protocol_encode(udp_packet,
			&udp_packet_len,
			s_PROTOCOL_ADDR_BROADCAST,
			g_config.robot_id,
			g_config.robot_team,
			s_PROTOCOL_TYPE_DATA,
			seq,
			g_message_sequence_id,
			last_id,
			data_type,
			data);

	// Broadcast packet
	udp_broadcast(g_udps, udp_packet, udp_packet_len);
	bytes_sent += udp_packet_len;

      }
      // Free memory*/
      free(data);
    }

    //printf("WE ARE HERE 1 \n");

/*
//send all found victims
while(victim_list->count != 0) {
printf("WE ARE HERE 2");
void *data = (void *)malloc(sizeof(victim_t));
doublylinkedlist_remove(victim_list, victim_list->first, data, &data_type);
      
protocol_encode(udp_packet,
&udp_packet_len,
s_PROTOCOL_ADDR_BROADCAST,
g_config.robot_id,
g_config.robot_team,
s_PROTOCOL_TYPE_DATA,
seq,
g_message_sequence_id,
last_id,
data_type,
data);
      
// Broadcast packet
bytes_sent += udp_packet_len;
udp_broadcast(g_udps, udp_packet, udp_packet_len);
      
free(data);
}

printf("WE ARE HERE 3");

doublylinkedlist_destroy(victim_list);

//Send the latest robot position
    

if (robot_list->count != 0) {
data = (void *)malloc(sizeof(robot_t));
doublylinkedlist_remove(robot_list, robot_list->first, data, &data_type);
    
protocol_encode(udp_packet,
&udp_packet_len,
s_PROTOCOL_ADDR_BROADCAST,
g_config.robot_id,
g_config.robot_team,
s_PROTOCOL_TYPE_DATA,
seq,
g_message_sequence_id,
last_id,
data_type,
data);
    
// Broadcast packet
bytes_sent += udp_packet_len;
udp_broadcast(g_udps, udp_packet, udp_packet_len);
    
free(data);
}
    
doublylinkedlist_destroy(robot_list);
    
printf("WE ARE HERE 4");
if (pheromone_list->count != 0) {
data = (void *)malloc(sizeof(pheromone_map_sector_t));
doublylinkedlist_remove(pheromone_list, pheromone_list->first, data, &data_type);
    
protocol_encode(udp_packet,
&udp_packet_len,
s_PROTOCOL_ADDR_BROADCAST,
g_config.robot_id,
g_config.robot_team,
s_PROTOCOL_TYPE_DATA,
seq,
g_message_sequence_id,
last_id,
data_type,
data);
    
// Broadcast packet
bytes_sent += udp_packet_len;
udp_broadcast(g_udps, udp_packet, udp_packet_len);
    
free(data);
}
    
doublylinkedlist_destroy(pheromone_list);
*/

    while (pheromone_list->count != 0 && bytes_sent < 1537) {
      data = (void *)malloc(sizeof(pheromone_map_sector_t));
      doublylinkedlist_remove(pheromone_list, pheromone_list->first, data, &data_type);
    
      protocol_encode(udp_packet,
		      &udp_packet_len,
		      s_PROTOCOL_ADDR_BROADCAST,
		      g_config.robot_id,
		      g_config.robot_team,
		      s_PROTOCOL_TYPE_DATA,
		      seq,
		      g_message_sequence_id,
		      last_id,
		      data_type,
		      data);
    
// Broadcast packet
      bytes_sent += udp_packet_len;
      udp_broadcast(g_udps, udp_packet, udp_packet_len);
    
      free(data);
    }

    
//    printf("Now here..... \n");
    //  printf("bytes sent: %d \n", bytes_sent);
    while(stream_list->count != 0 && bytes_sent < 1537) {
      //printf("WE ARE HERE 2 \n");
      // printf("SENDING BUFFERED STREAM DATA BECAUSE BYTES SENT IS ONLY %d \n", bytes_sent);
      void *data = (void *)malloc(sizeof(stream_t));
      doublylinkedlist_remove(stream_list, stream_list->first, data, &data_type);
    
      protocol_encode(udp_packet,
		      &udp_packet_len,
		      s_PROTOCOL_ADDR_BROADCAST,
		      g_config.robot_id,
		      g_config.robot_team,
		      s_PROTOCOL_TYPE_DATA,
		      seq,
		      g_message_sequence_id,
		      last_id,
		      data_type,
		      data);
    
      // Broadcast packet
      bytes_sent += udp_packet_len;
      udp_broadcast(g_udps, udp_packet, udp_packet_len);
      printf("BYTES SENT IS NOW: %d \n", bytes_sent);
      free(data);
    
      doublylinkedlist_destroy(stream_list);
      
    }



    /* --- Receive Data --- */
    // Receive packets, decode and forward to proper process

    // Receive UDP packet
    while(udp_receive(g_udps, udp_packet, &udp_packet_len) == s_OK)
    {
      // Decode packet
      //printf("%s\n",udp_packet);
      if(protocol_decode(&packet, udp_packet, udp_packet_len, g_config.robot_id, g_config.robot_team) == s_OK)
      {
	// Now decoding depends on the type of the packet
	switch(packet.type)
	{
	  // ACK
	  case s_PROTOCOL_TYPE_ACK :
	    // Do nothing
	    break;

	    //Massi: go_ahead packet
	  case s_PROTOCOL_TYPE_GO_AHEAD :
	  {
	    // Declare go ahead command 
	    command_t go_ahead;
	    go_ahead.cmd = s_CMD_GO_AHEAD;
	    // Redirect to mission by adding it to the queue
	    queue_enqueue(g_queue_mission, &go_ahead, s_DATA_STRUCT_TYPE_CMD);

	    // Debuging stuff
	    debug_printf("GO_AHEAD RECEIVED for robot %d team %d\n",packet.recv_id,packet.send_team);
	    // Calculate time from packet (ms and s)
	    int send_time_s = floor(packet.send_time / 1000);
	    int send_time_ms = packet.send_time % 1000;
	    int now = floor(((long long)timelib_unix_timestamp() % 60000) / 1000);
	    debug_printf("GO_AHEAD_TIME: %d (%d)\n",send_time_s,now);

	    break;
	  }
	  // Data
	  case s_PROTOCOL_TYPE_DATA :
	    // Continue depending on the data type
	    switch(packet.data_type)
	    {
	      // Robot pose
	      case s_DATA_STRUCT_TYPE_ROBOT :
		debug_printf("received robot\n");
		// Do nothing
		break;
		// Victim information
	      case s_DATA_STRUCT_TYPE_VICTIM :
		debug_printf("received victim\n");
		// Redirect to mission by adding it to the queue
		queue_enqueue(g_queue_mission, packet.data, s_DATA_STRUCT_TYPE_VICTIM);
		break;
		// Pheromone map
	      case s_DATA_STRUCT_TYPE_PHEROMONE :
		debug_printf("received pheromone\n");
		// Redirect to navigate by adding it to the queue
		queue_enqueue(g_queue_navigate, packet.data, s_DATA_STRUCT_TYPE_PHEROMONE);

		break;
		// Command
	      case s_DATA_STRUCT_TYPE_CMD :
		debug_printf("received CMD\n");
		// Redirect to mission by adding it to the queue
		queue_enqueue(g_queue_mission, packet.data, s_DATA_STRUCT_TYPE_CMD);
		break;
	      case s_DATA_STRUCT_TYPE_STREAM :
		debug_printf("received data stream item\n");
		break;
		// Other
	      default :
		// Do nothing
		break;
	    }
	    // Other ?
	  default:
	    // Do nothing
	    break;
	}

	// Free memory (only if data packet was received!)
	if(packet.type == s_PROTOCOL_TYPE_DATA)
	  free(packet.data);
      }
    }

    // Increase msg sequance id
    g_message_sequence_id++;
  }
}
