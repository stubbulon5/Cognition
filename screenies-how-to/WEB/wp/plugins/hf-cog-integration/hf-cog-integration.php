<?php
/*
Plugin Name: HarmonyFrameworks: Cognition App integration
Plugin URI: http://harmonyframeworks.com/
Description: Wordpress user and community integration with Cognition App 
Version: 1.0
Author: HarmonyFrameworks: Cognition App integration
Author URI: http://ultimatemember.com/
Text Domain: ultimate-member
*/
function add_user_token( $data ) {
    $return = array(
        'message' => __( 'TODO! ', 'textdomain' ),
        'output'  => "bla"
    );
    wp_send_json_success( $return );    
}

function validate_software_licence( $data ) {

    /*
        {
            "clientApp" : "cognition", 
            "clientAppVer" : "1.0", 
            "userLicence" : "abc123", 
            "userKey" : "user", 
            "userToken" : "token" 
        }
    */

    $jsonData = json_decode($data->get_body());

    $clientApp          = $jsonData->clientApp;
    $clientAppVer       = $jsonData->clientAppVer;
    $userLicence        = $jsonData->userLicence;
    $userKey            = $jsonData->userKey;
    $userToken          = $jsonData->userToken;


    $return = array(
        'message' => __( 'TODO: validate licence '.$userLicence.' against app '.$clientApp.'['.$clientAppVer.'] for user '.$userKey.'+'.$userToken, 'textdomain' )
    );
    wp_send_json_success( $return );

}


add_action( 'rest_api_init', function () {
    register_rest_route( 'hf_cog/v1', '/add_user_token', array(
        'methods' => 'POST',
        'callback' => 'add_user_token',
    ) );

    register_rest_route( 'hf_cog/v1', '/validate_licence', array(
        'methods' => 'POST',
        'callback' => 'validate_software_licence',
    ) );    
} );  
