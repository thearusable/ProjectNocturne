pipeline {

    environment {
        registry = "thearusable/nocturne"
        registryCredential = 'dockerhub'
    }

    //agent {
    //    docker { image 'thearusable/nocturne:latest' }
    //}

    //agent none
    agent { docker { image 'thearusable/nocturne:latest' } }

    //agent {
    //    dockerfile {
    //        filename 'Dockerfile'
    //        additionalBuildArgs '-t thearusable/nocturne'
    //    }
    //}

    stages {

        stage('Docker'){
            agent none
            steps{
                script{
                    // build docker image from dockerfile
                    sh 'docker build -t ${registry} .'
                    // publish image on docker hub
                    docker.withRegistry( '', registryCredential ) {
                        sh 'docker push ${registry}:latest'
                    }
                }
            }
        }

        //stage ('Build image') {
        //    steps{
        //        script {
                    // build image
        //            image = docker.build registry

                    // only push docker image when build from develop branch
        //            if (env.BRANCH_NAME == "develop"){
        //                docker.withRegistry('', registryCredential) {
        //                    image.push("latest")
        //                }
        //            } else {
        //                sh 'echo "Not a develop branch - SKIPPING."'
        //            }
        //        }
        //    }
        //}

        //stage ('Pre-analysis') {
        //    steps {
		//        sh 'cppcheck --enable=all --inconclusive --verbose --xml --xml-version=2 . 2> cppcheck_report.xml'
        //    }
        //}
        
        stage ('Build engine'){
            
            steps {
                dir('build')
                {
                    sh 'cmake ..'
                    sh 'make'
                }
            }
        }
    }
    //post {
	//    always {
	//        publishCppcheck pattern:'cppcheck_report.xml'
	//    }           
    //}
}
